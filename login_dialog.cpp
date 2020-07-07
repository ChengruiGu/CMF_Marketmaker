#include "login_dialog.h"
#include "ui_login_dialog.h"
#include <QMessageBox>

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("登录做市系统"));
    ui->user_lineEdit->setFocus();
}

Login_Dialog::~Login_Dialog()
{
    delete ui;
}

void Login_Dialog::on_pushButton_released()
{
    QString user = ui->user_lineEdit->text();
    QString pwd = ui->pwd_lineEdit_2->text();
    if(user == "")
            QMessageBox::warning(this,"", QString::fromLocal8Bit("用户名不能为空！"));
        else if(pwd == "")
            QMessageBox::warning(this,"",QString::fromLocal8Bit("密码不能为空！"));
    else{
        if(user == "cg" && pwd == "2020") {
            accept();
        }
        else {
            QMessageBox::warning(this, QString::fromLocal8Bit("警告！"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Yes);
            ui->user_lineEdit->clear();
            ui->pwd_lineEdit_2->clear();

            ui->user_lineEdit->setFocus();
        }
    }

}
