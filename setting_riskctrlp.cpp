#include "setting_riskctrlp.h"
#include "ui_setting_riskctrlp.h"

setting_riskctrlp::setting_riskctrlp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_riskctrlp)
{
    ui->setupUi(this);
}

setting_riskctrlp::~setting_riskctrlp()
{
    delete ui;
}
