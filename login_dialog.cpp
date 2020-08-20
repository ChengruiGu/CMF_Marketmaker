#include "login_dialog.h"
#include "ui_login_dialog.h"
#include <QMessageBox>

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("登录做市系统");

    //获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();


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
            QMessageBox::warning(this,"", "用户名不能为空！");
        else if(pwd == "")
            QMessageBox::warning(this,"","密码不能为空！");
    else{
        QSqlQuery sql_query;
        sql_query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
        sql_query.bindValue(":username", user);
        sql_query.bindValue(":password", pwd);
        sql_query.exec();

        if(sql_query.next()) {
            accept();
        }
        else {
            QMessageBox::warning(this, "警告！","用户名或密码错误！",QMessageBox::Yes);
            ui->user_lineEdit->clear();
            ui->pwd_lineEdit_2->clear();

            ui->user_lineEdit->setFocus();
        }
    }

}
