#include "setting_changepwd.h"
#include "ui_setting_changepwd.h"

setting_changepwd::setting_changepwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_changepwd)
{
    ui->setupUi(this);
}

setting_changepwd::~setting_changepwd()
{
    delete ui;
}
