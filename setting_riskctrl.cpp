#include "setting_riskctrl.h"
#include "ui_setting_riskctrl.h"

setting_riskctrl::setting_riskctrl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_riskctrl)
{
    ui->setupUi(this);
}

setting_riskctrl::~setting_riskctrl()
{
    delete ui;
}
