#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("            NOTE: Calculator restricted to inputs of 5 digits. Inaccurate results after 5 digits.");
}

Calculator::~Calculator()
{
    delete ui;
}

/*
 * TODO (not in orderly fashion):
 * Updated - 10:03 PM @ 02/12/24
 *
 * - Edit UI to where operation buttons will become different color when pressed
 * - Improve UI display
 *
 *
 * - If confident, try to add more operations in UI and program
 *
*/

/*
 * Current objective:
 * As of: 2:45 PM @ 02/14/24
 *
 * - Fix the integer/decimal issue (only grabbing integer version of expressions, may have to make whole algorithm double-based)
 *      > Almost fixed; adjust the delete button to properly set secondExp and resultLabel as such
 *
*/

/*
 * Completed in commit session:
 * As of: 2:45 PM @ 02/14/24
 *
 *
 *
*/

QString result;
double firstExp = 0.0, secondExp = 0.0, powerBase = 0.0, lastAns = 0.0;
bool add = false, subtract = false, multiply = false, divide = false, power = false;
bool secondResponse = false;

void Calculator::on_nineBtn_clicked()
{
    numberOperation(9);
}

void Calculator::on_eightBtn_clicked()
{
    numberOperation(8);
}

void Calculator::on_sevenBtn_clicked()
{
    numberOperation(7);
}

void Calculator::on_sixBtn_clicked()
{
    numberOperation(6);
}

void Calculator::on_fiveBtn_clicked()
{
    numberOperation(5);
}

void Calculator::on_fourBtn_clicked()
{
    numberOperation(4);
}

void Calculator::on_threeBtn_clicked()
{
    numberOperation(3);
}

void Calculator::on_twoBtn_clicked()
{
    numberOperation(2);
}

void Calculator::on_oneBtn_clicked()
{
    numberOperation(1);
}

void Calculator::on_zeroBtn_clicked()
{
    result = ui -> resultLabel -> text();
    if(result.toDouble() != 0.0 || result.contains('.')) {

        ui -> clearBtn -> setText("Clear");
        result += QString::number(0);
        ui -> resultLabel -> setText(result);

        secondExp = result.toDouble();
    }
}

void Calculator::numberOperation(int number)
{
    ui -> clearBtn -> setText("Clear");
    result = ui -> resultLabel -> text();

    if(secondResponse || result.toDouble() - lastAns == 0.0) {
        result = "0";
        secondResponse = false;
    }

    if((result.contains('.') && result.length() < 6) || result.length() < 5) {
        if(result != "0") {
            result += QString::number(number);
            ui -> resultLabel -> setText(result);

        } else {
            result = QString::number(number);
            ui -> resultLabel -> setText(result);
        }

    secondExp = result.toDouble();
    }

}

void Calculator::on_decimalBtn_clicked()
{
    ui -> clearBtn -> setText("Clear");
    result = ui -> resultLabel -> text();

    if(secondResponse) {
        result = "0";
        secondResponse = false;
    }

    if(result.length() < 5 && !result.contains('.')) {
         ui -> resultLabel -> setText(result + QChar('.'));
    }
}

void Calculator::on_lastAnsBtn_clicked()
{
    ui -> clearBtn -> setText("Clear");

    secondExp = lastAns;
    ui -> resultLabel -> setText(QString::number(secondExp));
}

void Calculator::actualOperation()
{
    if(power) {
        int i = 1;
        while (i < secondExp) {
            firstExp *= powerBase;
            i++;
        }
    }

    if(add) {
        firstExp += secondExp;
    }

    if(subtract) {
        firstExp -= secondExp;
    }

    if(multiply) {
        firstExp *= secondExp;
    }

    if(divide) {
        firstExp /= secondExp;
    }

    if(!add && !subtract && !multiply && !divide && !power) {
        if(secondExp != 0.0) {
            firstExp = secondExp;
        }
    }

    secondExp = 0.0;
    ui -> resultLabel -> setText(QString::number(firstExp));
    add = subtract = multiply = divide = power = false;
    secondResponse = true;
}

void Calculator::on_equalBtn_clicked()
{
    Calculator::actualOperation();
    lastAns = firstExp;
    secondResponse = false;
}

void Calculator::on_clearBtn_clicked()
{
    ui -> resultLabel -> setText(QString::number(0));

    if(ui -> clearBtn -> text() == "AC") {
        firstExp = secondExp = lastAns = 0;
        add = subtract = multiply = divide = power = secondResponse = false;

        ui -> clearBtn -> setText("Clear");
    } else {
        secondExp = 0;
        ui -> clearBtn -> setText("AC");
    }
}

void Calculator::on_deleteBtn_clicked()
{
    result = ui -> resultLabel -> text();
    if(result.toLong() != 0 || result.contains('.')) {
        secondExp = result.removeLast().toLong();

        if(result.length() == 0) {
            ui -> resultLabel -> setText(QString::number(0));
        } else {
            ui -> resultLabel -> setText(result);
        }
    }
}

void Calculator::on_plusBtn_clicked()
{
    Calculator::actualOperation();
    add = true;
}

void Calculator::on_subtractBtn_clicked()
{
    Calculator::actualOperation();
    subtract = true;
}

void Calculator::on_multBtn_clicked()
{
    Calculator::actualOperation();
    multiply = true;
}

void Calculator::on_divideBtn_clicked()
{
    Calculator::actualOperation();
    divide = true;
}

void Calculator::on_powerBtn_clicked()
{
    Calculator::actualOperation();
    powerBase = firstExp;
    power = true;
}
