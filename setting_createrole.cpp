#include "setting_createrole.h"
#include "ui_setting_createrole.h"

/*
*
* Create the window of creating new role
*/
setting_createRole::setting_createRole(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::setting_createRole)
{
    ui->setupUi(this);
}

setting_createRole::~setting_createRole()
{
    delete ui;
}

void setting_createRole::on_pushButton_released()
{
    accept();
}
