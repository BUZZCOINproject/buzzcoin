#include "charitydialog.h"
#include "ui_charitydialog.h"

#include "clientmodel.h"
#include "notificator.h"
#include "version.h"

#include "wallet.h"
#include "walletdb.h"
#include "main.h"
#include "init.h"

charityDialog::charityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::charityDialog)
{
    CBitcoinAddress address;
    int nCharityPercent;
    Notificator *notificator = new Notificator();
    
    ui->setupUi(this);
    if (pwalletMain->IsLocked())
    {
        notificator->notify(Notificator::Warning, tr("Error!"), tr("Please unlock your wallet first."));
        return;
    }

    address = pwalletMain->StakeForCharityAddress;
    nCharityPercent = pwalletMain->nStakeForCharityPercent;
    
    ui->charityPercentSb->setValue(nCharityPercent);

    if (address.IsValid()) {
        ui->charityAddressEdit->setText(QString::fromStdString(address.ToString()));
        ui->charityAddress->setText(QString::fromStdString(address.ToString()));
    }
    
    if (this->model->isTestNet()) {
        ui->charityAddress->setVisible(false);
        ui->charityAddressEdit->setVisible(true);
        ui->testNetLabel->setVisible(true);
    } else {
        ui->charityAddress->setVisible(true);
        ui->charityAddressEdit->setVisible(false);
        ui->testNetLabel->setVisible(false);

    }
}

charityDialog::~charityDialog()
{
    delete ui;
}

void charityDialog::setModel(ClientModel *model)
{
    this->model = model;
}

void charityDialog::on_buttonBox_accepted()
{
    CBitcoinAddress address;
    int nCharityPercent;

    Notificator *notificator;
    notificator = new Notificator();

    // Empty address? Defaults to dev wallet
    if (ui->charityAddressEdit->text().isEmpty())
    {
        address = "BRfGmqCg6kKBwWTzzMVYoq3BXp2t6oWAzx";
    } else {
        address = ui->charityAddressEdit->text().toStdString();
    }

    if (!address.IsValid())
    {
        notificator->notify(Notificator::Warning, tr("Invalid!"), tr("Ensure you are using a proper BUZZ address."));
        return;
    }

    nCharityPercent = ui->charityPercentSb->value();

    // limit to a range between 5-100, otherwise default to 5%
    if (nCharityPercent <= 5 || nCharityPercent > 100)
        nCharityPercent = 5;

    if (pwalletMain->IsLocked())
    {
        notificator->notify(Notificator::Warning, tr("Error!"), tr("Please unlock your wallet first."));
        return;
    }

    pwalletMain->fStakeForCharity = true;
    pwalletMain->StakeForCharityAddress = address.ToString();
    pwalletMain->nStakeForCharityPercent = nCharityPercent;

    CWalletDB walletdb(pwalletMain->strWalletFile);

    LOCK(pwalletMain->cs_wallet);
    {
        if (pwalletMain->fFileBacked)
        {
            walletdb.WriteStakeForCharityEnabled(pwalletMain->fStakeForCharity);
            walletdb.WriteStakeForCharityPercentage(nCharityPercent);
            walletdb.WriteStakeForCharityAddress(address.ToString());
            notificator->notify(Notificator::Information, tr("Success!"), tr("Development Support settings saved to wallet.dat!"));
        } else {  
            notificator->notify(Notificator::Warning, tr("Failure!"), tr("Development Support settings NOT saved to wallet.dat!"));
        }
    }
    close();
}

void charityDialog::on_buttonBox_rejected()
{
    close();
}
