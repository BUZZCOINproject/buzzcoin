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

    nCharityPercent = ui->charityPercentEdit->text().toInt();

    // limit to a range between 0-100, otherwise default to 1%
    if (nCharityPercent < 0 || nCharityPercent > 100)
        nCharityPercent = 1;

    if (pwalletMain->IsLocked())
    {
        notificator->notify(Notificator::Warning, tr("Error!"), tr("Please unlock your wallet first."));
        return;
    }

    // disable S4C if percentage is set to 0.
    if (nCharityPercent == 0)
    {
        pwalletMain->fStakeForCharity = false;
        notificator->notify(Notificator::Information, tr("Success!"), tr("Development Support Disabled"));
    } else {
        pwalletMain->fStakeForCharity = true;
    }

    pwalletMain->StakeForCharityAddress = address.ToString();
    pwalletMain->nStakeForCharityPercent = nCharityPercent;

    CWalletDB walletdb(pwalletMain->strWalletFile);

    LOCK(pwalletMain->cs_wallet);
    {
        if (pwalletMain->fFileBacked)
        {
            walletdb.WriteStakeForCharityEnabled(nCharityPercent <= 0 ? false : true);
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
