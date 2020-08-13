#include "setting_createrole.h"
#include "ui_setting_createrole.h"

#include <QMessageBox>

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
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.open()) {
        qWarning("cannot open db in createrole");
        return;
    }
    QString username = ui->lineEdit->text();
    username.replace(QString(" "),QString(""));

    QString password = ui->lineEdit_2->text();
    password.replace(QString(" "),QString(""));

    QString name = ui->lineEdit_3->text();
    name.replace(QString(" "),QString(""));

    QString phone = ui->lineEdit_4->text();
    phone.replace(QString(" "),QString(""));

    QString email = ui->lineEdit_5->text();
    email.replace(QString(" "),QString(""));

    QString role;
    if(ui->radioButton->isChecked()){
        role = "管理员";
    } else if(ui->radioButton_2->isChecked()){
        role = "风控员";
    } else if(ui->radioButton_3->isChecked()){
        role = "交易员";
    } else if(ui->radioButton_4->isChecked()){
        role = "IT";
    } else {
        role = "";
    }

    if(username.isEmpty() || password.isEmpty() || name.isEmpty() || phone.isEmpty() || email.isEmpty() || role.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("输入不能为空！");
        msgBox.exec();
        return;
    }

//    QSqlRecord record;
//    record.append(QSqlField("username"));
//    record.append(QSqlField("name"));
//    record.append(QSqlField("role"));
//    record.append(QSqlField("phone"));
//    record.append(QSqlField("email"));
//    record.append(QSqlField("date"));
//    record.append(QSqlField("password"));

//    record.setValue("username", username);
//    record.setValue("name", name);
//    record.setValue("role", role);
//    record.setValue("phone", phone);
//    record.setValue("email", email);
//    record.setValue("password", password);

    QDate current = QDate::currentDate();
    QString date = current.toString("yyyy-MM-dd");
    //record.setValue("date", current.toString("yyyy-MM-dd"));

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, name, role, phone, email, date, password) "
                      "VALUES(:username, :name, :role, :phone, :email, :date, :password)");
    query.bindValue(":username", username);
    query.bindValue(":name", name);
    query.bindValue(":role", role);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":date", date);
    query.bindValue(":password", password);

    query.exec();

    accept();
}
