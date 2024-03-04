#include "calculator.h"
#include "ui_calculator.h"
#include <QObject>

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
 * Updated - 1:28 PM @ 03/03/24
 *
 * - Try to add a desktop picture/logo
 * - Release application to macOS users
 * - (try to) Release application to Windows users
 * - Increase digit restrictions (starting from 7)
 *
 * - If confident, try to add more operations in UI and program
 *
*/

/*
 * Current objective:
 * As of: 1:28 PM @ 02/03/24
 *
 * - Add comments for functions for readability
 *
*/

/*
 * Completed in commit session:
 * Starting at: 1:40 PM @ 02/28/24
 *
 * - Adjust decimalButton to where button will be hidden when doing an operation
 * - Adjust zero button where, after inputting operation button, pressing zero will make display only show 0
 *      > Program somehow adds 0 to first number after operation button pressed
 * - Adjust operation buttons where primary style sheet reappars when inputting second number
 *
*/

QString result;
double firstExp = 0.0, secondExp = 0.0, powerBase = 0.0, lastAns = 0.0;
bool add = false, subtract = false, multiply = false, divide = false, power = false;
bool secondResponse = false;

QString pressedStyleSheet = "QPushButton{ background-color: white; color: orange }",
        currentStyleSheet = "QPushButton{ background-color: orange; } QPushButton:hover{ background-color: #d3d3d3; }",
        acStyleSheet = "QPushButton{ background-color: white; color: blue; } QPushButton:hover{ color: #d3d3d3 }",
        clearStyleSheet = "QPushButton{ background-color: blue; } QPushButton:hover{ background-color: #aed8e6; }";



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
    numberOperation(0);
}

void Calculator::on_decimalBtn_clicked()
{
    ui -> clearBtn -> setText("Clear");
    ui -> decimalBtn -> hide();
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
        ui -> clearBtn -> setStyleSheet(clearStyleSheet);
    } else {
        secondExp = 0;
        ui -> clearBtn -> setText("AC");
        ui -> clearBtn -> setStyleSheet(acStyleSheet);

        (add) ? ui->plusBtn->setStyleSheet(pressedStyleSheet) : void();
        (subtract) ? ui->subtractBtn->setStyleSheet(pressedStyleSheet) : void();
        (multiply) ? ui->multBtn->setStyleSheet(pressedStyleSheet) : void();
        (divide) ? ui->divideBtn->setStyleSheet(pressedStyleSheet) : void();
        (power) ? ui->powerBtn->setStyleSheet(pressedStyleSheet) : void();
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

    ui -> plusBtn -> setStyleSheet(pressedStyleSheet);

}

void Calculator::on_subtractBtn_clicked()
{
    Calculator::actualOperation();
    subtract = true;

    ui -> subtractBtn -> setStyleSheet(pressedStyleSheet);
}

void Calculator::on_multBtn_clicked()
{
    Calculator::actualOperation();
    multiply = true;

    ui -> multBtn -> setStyleSheet(pressedStyleSheet);
}

void Calculator::on_divideBtn_clicked()
{
    Calculator::actualOperation();
    divide = true;

    ui -> divideBtn -> setStyleSheet(pressedStyleSheet);
}

void Calculator::on_powerBtn_clicked()
{
    Calculator::actualOperation();
    powerBase = firstExp;
    power = true;

    ui -> powerBtn -> setStyleSheet(pressedStyleSheet);
}

void Calculator::numberOperation(int number)
{
    ui -> clearBtn -> setText("Clear");
    ui -> clearBtn -> setStyleSheet(clearStyleSheet);

    result = ui -> resultLabel -> text();

    if(result != "0." && (secondResponse || result.toDouble() - lastAns == 0.0)) {
        result = "0";
        secondResponse = false;

        (add) ? ui->plusBtn->setStyleSheet(currentStyleSheet) : void();
        (subtract) ? ui->subtractBtn->setStyleSheet(currentStyleSheet) : void();
        (multiply) ? ui->multBtn->setStyleSheet(currentStyleSheet) : void();
        (divide) ? ui->divideBtn->setStyleSheet(currentStyleSheet) : void();
        (power) ? ui->powerBtn->setStyleSheet(currentStyleSheet) : void();
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

void Calculator::actualOperation()
{

    if(power) {
        int i = 1;
        while (i < secondExp) {
            firstExp *= powerBase;
            i++;
        }

        ui->powerBtn->setStyleSheet(currentStyleSheet);
    }

    if(add) {
        firstExp += secondExp;
        ui->plusBtn->setStyleSheet(currentStyleSheet);
    }

    if(subtract) {
        firstExp -= secondExp;
        ui->subtractBtn->setStyleSheet(currentStyleSheet);
    }

    if(multiply) {
        firstExp *= secondExp;
        ui->multBtn->setStyleSheet(currentStyleSheet);
    }

    if(divide) {
        firstExp /= secondExp;
        ui->divideBtn->setStyleSheet(currentStyleSheet);
    }

    if(!add && !subtract && !multiply && !divide && !power) {
        if(secondExp != 0.0) {
            firstExp = secondExp;
        }
    }

    secondExp = 0.0;

    ui -> resultLabel -> setText(QString::number(firstExp));
    ui -> decimalBtn -> show();

    add = subtract = multiply = divide = power = false;
    secondResponse = true;
}
