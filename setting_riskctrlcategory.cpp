#include "setting_riskctrlcategory.h"
#include "ui_setting_riskctrlcategory.h"

setting_riskctrlcategory::setting_riskctrlcategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_riskctrlcategory)
{
    ui->setupUi(this);
}

setting_riskctrlcategory::~setting_riskctrlcategory()
{
    delete ui;
}
