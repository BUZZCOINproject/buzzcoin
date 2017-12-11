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
    ui->setupUi(this);
}

charityDialog::~charityDialog()
{
    delete ui;
}

void charityDialog::setModel(ClientModel *model)
{

}

void charityDialog::on_buttonBox_accepted()
{
    CBitcoinAddress address = ui->charityAddressEdit->text().toStdString();

    if (!address.IsValid())
    {
        notificator->notify(Notificator::Warning, tr("Invalid BUZZ address"));
    }

    QString str = ui->charityPercentEdit->text();
    bool fIntConversion;
    unsigned int nCharityPercent = str.toInt(&fIntConversion, 10);

    if (nCharityPercent < 0)
    {
        notificator->notify(Notificator::Warning, tr("Invalid parameter, expected valid percentage"));
    }

    if (pwalletMain->IsLocked())
    {
        notificator->notify(Notificator::Warning, tr("Error: Please unlock your wallet first."));
    }

    if (nCharityPercentx <= 0)
    {
        pwalletMain->fStakeForCharity = false;
        pwalletMain->StakeForCharityAddress = "";
        pwalletMain->nStakeForCharityPercent = 0;
        notificator->notify(Notificator::Information, tr("Stake for Charity Disabled!"));
        close();
    } else {
        pwalletMain->StakeForCharityAddress = address;
        pwalletMain->nStakeForCharityPercent = nCharityPercentx;
        pwalletMain->fStakeForCharity = true;
    }

    LOCK(pwalletMain->cs_wallet);
    {

        if (pwalletMain->fFileBacked)
        {
            walletdb.WriteStakeForCharityEnabled(fStakeForCharity);
            walletdb.WriteStakeForCharityPercentage(nStakeForCharityPercent);
            walletdb.WriteStakeForCharityAddress(StakeForCharityAddress);
            notificator->notify(Notificator::Information, tr("Stake for Charity settings saved to wallet.dat!"));
        } else {  
            notificator->notify(Notificator::Warning, tr("Stake for Charity settings NOT saved to wallet.dat!"));
        }
    }
    close();
}

void charityDialog::on_buttonBox_rejected()
{
    close();
}
