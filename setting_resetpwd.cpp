#include "setting_resetpwd.h"
#include "ui_setting_resetpwd.h"
#include <QMessageBox>

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

void setting_resetPwd::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    msgBox.setText("密码已重置！");

    msgBox.exec();
}
