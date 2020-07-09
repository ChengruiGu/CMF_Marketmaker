#include "setting_resetpwd.h"
#include "ui_setting_resetpwd.h"

setting_resetPwd::setting_resetPwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_resetPwd)
{
    ui->setupUi(this);
}

setting_resetPwd::~setting_resetPwd()
{
    delete ui;
}
