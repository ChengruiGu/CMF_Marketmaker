#include "setting_riskprmt.h"
#include "ui_setting_riskprmt.h"

#include <QFileDialog>

setting_riskprmt::setting_riskprmt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_riskprmt)
{
    ui->setupUi(this);
}

setting_riskprmt::~setting_riskprmt()
{
    delete ui;
}

void setting_riskprmt::on_pushButton_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    ui->label_5->setText(file_name);
}

void setting_riskprmt::on_pushButton_2_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    ui->label_6->setText(file_name);
}

void setting_riskprmt::on_pushButton_3_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    ui->label_7->setText(file_name);
}
