#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:

    void on_nineBtn_clicked();

    void on_eightBtn_clicked();

    void on_sevenBtn_clicked();

    void on_sixBtn_clicked();

    void on_fiveBtn_clicked();

    void on_fourBtn_clicked();

    void on_threeBtn_clicked();

    void on_twoBtn_clicked();

    void on_oneBtn_clicked();

    void on_zeroBtn_clicked();

    void on_decimalBtn_clicked();

    void on_lastAnsBtn_clicked();

    void on_equalBtn_clicked();

    void on_clearBtn_clicked();

    void on_plusBtn_clicked();

    void on_subtractBtn_clicked();

    void on_multBtn_clicked();

    void on_deleteBtn_clicked();

    void on_divideBtn_clicked();

    void on_powerBtn_clicked();



private:

    void numberOperation(int number);

    void actualOperation();

    Ui::Calculator *ui;
};
#endif // CALCULATOR_H
