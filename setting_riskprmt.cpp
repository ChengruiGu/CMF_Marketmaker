#include "setting_riskprmt.h"
#include "ui_setting_riskprmt.h"

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
