#include "unittestdialog.h"
#include "ui_unittestdialog.h"
#include "clientmodel.h"
#include "main.h"
#include "util.h"
#include "version.h"

#include <QStandardItem>

UnitTestDialog::UnitTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitTestDialog)
{
    ui->setupUi(this);
    
    // setup preset combo box
    presetComboBox = ui->presetComboBox;
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(presetComboBox->model());
    QStandardItem* item;
    
    presetComboBox->addItem(tr("None"));
    presetComboBox->addItem(tr("New Preset"));
    presetComboBox->addItem(tr("Delete Selected"));
    presetComboBox->insertSeparator(1);
    item = model->item(0);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    item = model->item(2);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    item = model->item(3);
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);


}

void UnitTestDialog::setModel(ClientModel *model)
{
}

UnitTestDialog::~UnitTestDialog()
{
    delete ui;
}

void UnitTestDialog::stateChangedCb1(int state) {

}
void UnitTestDialog::stateChangedCb2(int state) {
    
}
void UnitTestDialog::stateChangedCb3(int state) {
    
}

void UnitTestDialog::test1() {
    // int64_t GetCoinYearReward(CBlockIndex* pindex)

    //debug vars
    bool lDebug = fDebug, lPrintToConsole = fPrintToConsole;
    
    int64_t value = 0;
    CBlockIndex* pindex = new CBlockIndex();
    pindex->nHeight = ui->le2B->text().toInt();
    pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;
    
    // loop thru
    int64_t item1_stop = ui->le1E->text().toLongLong() * COIN; // currentSupply
    int64_t item2_stop = ui->le2E->text().toLongLong(); // currentHeight
    int64_t item1_step = ui->le1S->text().toLongLong() * COIN; // currentSupply
    int64_t item2_step = ui->le2S->text().toLongLong(); // currentHeight
    
   // save debug vars
    if (fDebug) fDebug = false;
    if (fPrintToConsole) fPrintToConsole = false;
    
    ui->plainTextEdit->appendPlainText(
                                       QString("GetCoinYearReward\ncurrentHeight\tcurrentSupply\tyearReward"));
    
    do { // nHeight loop
        do { // moneySupply loop
            value = GetCoinYearReward(pindex);
            ui->plainTextEdit->appendPlainText(
                                               QString("%1\t%2\t%3")
                                               .arg(QString::number(pindex->nHeight),
                                                    QString::number((pindex->nMoneySupply / COIN)),
                                                    QString::number((double)(value / CENT)))
                                               );
            
            if (!ui->cb1->isChecked()) break;
            
            pindex->nMoneySupply += item1_step;
            
        } while (pindex->nMoneySupply <= item1_stop);
        
        pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;
        
        if (!ui->cb2->isChecked()) break;
        
        pindex->nHeight += item2_step;
        
    } while (pindex->nHeight <= item2_stop);
    

    // reset vars
    fDebug = lDebug; fPrintToConsole = lPrintToConsole;

}

void UnitTestDialog::test2() {
    // int64_t GetProofOfStakeReward(int64_t nCoinAge, int64_t nFees, CBlockIndex* pindex)

    //debug vars
    bool lDebug = fDebug, lPrintToConsole = fPrintToConsole;
    
    int64_t value = 0;
    int64_t coinAge = 0;
    CBlockIndex* pindex = new CBlockIndex();
    pindex->nHeight = ui->le2B->text().toInt();
    pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;
    coinAge = ui->le3B->text().toLongLong();
    
    // loop thru
    int64_t item1_stop = ui->le1E->text().toLongLong() * COIN; // currentSupply
    int64_t item2_stop = ui->le2E->text().toLongLong(); // currentHeight
    int64_t item3_stop = ui->le3E->text().toLongLong(); // coinAge
    int64_t item1_step = ui->le1S->text().toLongLong() * COIN; // currentSupply
    int64_t item2_step = ui->le2S->text().toLongLong(); // currentHeight
    int64_t item3_step = ui->le3S->text().toLongLong(); // coinAge

    // save debug vars
    if (fDebug) fDebug = false;
    if (fPrintToConsole) fPrintToConsole = false;

    ui->plainTextEdit->appendPlainText(
                                       QString("GetProofOfStakeReward\ncurrentHeight\tcurrentSupply\tcoinAge\tcreate"));
    
    
    do { // nHeight loop
        do { // moneySupply loop
            do { // coinAge loop
                value = GetProofOfStakeReward(coinAge,0,pindex);
                ui->plainTextEdit->appendPlainText(
                                               QString("%1\t%2\t%3\t%4")
                                               .arg(QString::number(pindex->nHeight),
                                                    QString::number((pindex->nMoneySupply / COIN)),
                                                    QString::number(coinAge),
                                                    QString::fromStdString(FormatMoney(value)))
                                               );
                if (!ui->cb3->isChecked()) break;
                coinAge += item3_step;
            } while (coinAge <= item3_stop);

            if (!ui->cb1->isChecked()) break;
            
            pindex->nMoneySupply += item1_step;
            
        } while (pindex->nMoneySupply <= item1_stop);
        
        pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;
        
        if (!ui->cb2->isChecked()) break;
        
        pindex->nHeight += item2_step;
        
    } while (pindex->nHeight <= item2_stop);

    // reset vars
    fDebug = lDebug; fPrintToConsole = lPrintToConsole;

}

void UnitTestDialog::test3() {
    // int64_t GetProofOfWorkReward(int64_t nFees, CBlockIndex* pindex);

    //debug vars
    bool lDebug = fDebug, lPrintToConsole = fPrintToConsole;
    
    int64_t value = 0;
    CBlockIndex* pindex = new CBlockIndex();
    pindex->nHeight = ui->le2B->text().toInt();
    pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;

    // loop thru
    int64_t item1_stop = ui->le1E->text().toLongLong() * COIN; // currentSupply
    int64_t item2_stop = ui->le2E->text().toLongLong(); // currentHeight
    int64_t item1_step = ui->le1S->text().toLongLong() * COIN; // currentSupply
    int64_t item2_step = ui->le2S->text().toLongLong(); // currentHeight

    // save debug vars
    if (fDebug) fDebug = false;
    if (fPrintToConsole) fPrintToConsole = false;

    ui->plainTextEdit->appendPlainText(
                                       QString("GetProofOfWorkReward\ncurrentHeight\tcurrentSupply\tcreate\tnSubsidy"));

    do { // nHeight loop
        do { // moneySupply loop
            value = GetProofOfWorkReward(0,pindex);
            ui->plainTextEdit->appendPlainText(
                                               QString("%1\t%2\t%3\t%4")
                                               .arg(QString::number(pindex->nHeight),
                                                    QString::number((pindex->nMoneySupply / COIN)),
                                                    QString::number((double)(value / COIN)),
                                                    QString::number(value))
                                               );

            if (!ui->cb1->isChecked()) break;
            
            pindex->nMoneySupply += item1_step;
            
        } while (pindex->nMoneySupply <= item1_stop);
        
        pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;
        
        if (!ui->cb2->isChecked()) break;
        
        pindex->nHeight += item2_step;
        
    } while (pindex->nHeight <= item2_stop);
    
    // reset vars
    fDebug = lDebug; fPrintToConsole = lPrintToConsole;
}

void UnitTestDialog::test4() {
    // int GetMinStakeAge(CBlockIndex* pindex)

    //debug vars
    bool lDebug = fDebug, lPrintToConsole = fPrintToConsole;
    
    int64_t value = 0;
    CBlockIndex* pindex = new CBlockIndex();
    pindex->nHeight = ui->le2B->text().toInt();
    pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;

    // loop thru
    int64_t item1_stop = ui->le1E->text().toLongLong() * COIN; // currentSupply
    int64_t item2_stop = ui->le2E->text().toLongLong(); // currentHeight
    int64_t item1_step = ui->le1S->text().toLongLong() * COIN; // currentSupply
    int64_t item2_step = ui->le2S->text().toLongLong(); // currentHeight

    // save debug vars
    if (fDebug) fDebug = false;
    if (fPrintToConsole) fPrintToConsole = false;

    ui->plainTextEdit->appendPlainText(
                                       QString("GetMinStakeAge\ncurrentHeight\tcurrentSupply\tminAge\tminStakeAge"));

    do { // nHeight loop
        do { // moneySupply loop
            value = GetMinStakeAge(pindex);
            ui->plainTextEdit->appendPlainText(
                                           QString("%1\t%2\t%3\t%4")
                                           .arg(QString::number(pindex->nHeight),
                                                QString::number((pindex->nMoneySupply / COIN)),
                                                QString::number((double)value/60/60/24),
                                                QString::number((double)value)
                                                )
                                           );
        
            if (!ui->cb1->isChecked()) break;
            
            pindex->nMoneySupply += item1_step;

        } while (pindex->nMoneySupply <= item1_stop);

        pindex->nMoneySupply = ui->le1B->text().toLongLong() * COIN;

        if (!ui->cb2->isChecked()) break;

        pindex->nHeight += item2_step;
        
    } while (pindex->nHeight <= item2_stop);

    // reset vars
    fDebug = lDebug; fPrintToConsole = lPrintToConsole;
}
void UnitTestDialog::clear() {
    ui->plainTextEdit->clear();
}
