#include "login_dialog.h"
#include "ui_login_dialog.h"
#include <QMessageBox>

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("��¼����ϵͳ"));
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
            QMessageBox::warning(this,"", QString::fromLocal8Bit("�û�������Ϊ�գ�"));
        else if(pwd == "")
            QMessageBox::warning(this,"",QString::fromLocal8Bit("���벻��Ϊ�գ�"));
    else{
        if(user == "cg" && pwd == "2020") {
            accept();
        }
        else {
            QMessageBox::warning(this, QString::fromLocal8Bit("���棡"),QString::fromLocal8Bit("�û������������"),QMessageBox::Yes);
            ui->user_lineEdit->clear();
            ui->pwd_lineEdit_2->clear();

            ui->user_lineEdit->setFocus();
        }
    }

}
