#ifndef UNITTESTDIALOG_H
#define UNITTESTDIALOG_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
    class UnitTestDialog;
}
class ClientModel;

/** "About" dialog box */
class UnitTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnitTestDialog(QWidget *parent = 0);
    ~UnitTestDialog();

    void setModel(ClientModel *model);
private:
    Ui::UnitTestDialog *ui;
    QComboBox   *presetComboBox;
    
private slots:
    void test1();
    void test2();
    void test3();
    void test4();
    void stateChangedCb1(int state);
    void stateChangedCb2(int state);
    void stateChangedCb3(int state);
    void clear();
};

#endif // UNITTESTDIALOG_H
