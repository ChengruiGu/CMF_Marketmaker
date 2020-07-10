#include "setting_setmm.h"
#include "ui_setting_setmm.h"

setting_setmm::setting_setmm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_setmm)
{
    ui->setupUi(this);
}

setting_setmm::~setting_setmm()
{
    delete ui;
}
