#include "disclaimer.h"
#include "ui_disclaimer.h"

#include "clientmodel.h"
#include "notificator.h"
#include "version.h"

#include "main.h"
#include "init.h"

#include <QSettings>
#include <QTimer>

disclaimer::disclaimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::disclaimer)
{
    ui->setupUi(this);
    ui->pbAG->setEnabled(false);
}

disclaimer::~disclaimer()
{
    delete ui;
}

void disclaimer::setModel(ClientModel *model)
{
    this->model = model;
}

void disclaimer::reject()
{
    QDialog::reject();
    
    QSettings settings;
    settings.setValue("disclaimer/agreed_threeoh", false);
    
    QCoreApplication::quit();
}

void disclaimer::accept()
{
    QDialog::accept();
    this->performAction();
}

void disclaimer::stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->pbAG->setEnabled(true);
    } else {
        ui->pbAG->setEnabled(false);
    }
}

void disclaimer::performAction()
{
    QSettings settings;
    Qt::CheckState state = ui->agreeCb->checkState();
    if (state == Qt::Checked) {
        settings.setValue("disclaimer/agreed_threeoh", true);
    } else {
        settings.setValue("disclaimer/agreed_threeoh", false);
        QCoreApplication::quit();
    }

}
