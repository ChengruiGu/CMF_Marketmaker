#include "account_login.h"
#include "ui_account_login.h"

account_login::account_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account_login)
{
    ui->setupUi(this);
}

account_login::~account_login()
{
    delete ui;
}
