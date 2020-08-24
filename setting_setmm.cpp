#include "setting_setmm.h"
#include "ui_setting_setmm.h"

/* 代码结构与setting_uploadstrategies非常相似 */
setting_setmm::setting_setmm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_setmm)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);

    model->setColumnCount(1);

    QSqlQuery sql_query;
    if(!sql_query.exec("SELECT username FROM users "
                       "WHERE role = '管理员' OR role = '交易员'")) qDebug() << sql_query.lastError();
    int i = 0;
    while(sql_query.next()){
        QString username = sql_query.value(0).toString();
        model->appendRow(new QStandardItem(username));
        ++i;
    }
    ui->listView->setModel(model);


    sql_query.exec("SELECT contract_code FROM future_contracts");
    while(sql_query.next()){
        QString name = sql_query.value(0).toString();
        //qDebug() << name;
        QCheckBox* cb = new QCheckBox(name);
        contracts[name] = cb;
        ui->formLayout->addWidget(cb);
    }

}

setting_setmm::~setting_setmm()
{
    delete ui;
}

/* 点击左侧交易员栏 响应事件 */
void setting_setmm::on_listView_clicked(const QModelIndex &index)
{

    QString username = model->data(index).toString();
    //qDebug() << username;
    QSqlQuery sql_query;
    sql_query.prepare("SELECT contract_code "
                      "FROM user_contracts "
                      "WHERE username = :username");
    sql_query.bindValue(":username",username);

    if(!sql_query.exec()) qDebug() << sql_query.lastError();
    clear_checkboxes();
    while(sql_query.next()){
        QString contract_code = sql_query.value(0).toString();
        contracts[contract_code]->setChecked(true);
    }
    ui->label->setText(username);
}

/* 点击确认按钮 */
void setting_setmm::on_pushButton_released()
{
    QString username = ui->label->text();
    if(username.isEmpty()) return;
    QSqlQuery sql_query;
    QMap<QString, QCheckBox*>::const_iterator i = contracts.constBegin();
    while (i != contracts.constEnd()) {
        if(i.value()->isChecked()){ //如果被打钩则添加
            //qDebug() << "hello";
            sql_query.prepare("INSERT INTO user_contracts VALUES(:username, :contract_code)");
            sql_query.bindValue(":username", username);
            sql_query.bindValue(":contract_code", i.value()->text());

            if(!sql_query.exec()) qDebug() << sql_query.lastError();
        } else { //如果没被打钩则删除权限
            sql_query.prepare("DELETE FROM user_contracts "
                              "WHERE username = :username AND contract_code = :contract_code");
            sql_query.bindValue(":username", username);
            sql_query.bindValue(":contract_code", i.value()->text());
            if(!sql_query.exec()) qDebug() << sql_query.lastError();
        }
        ++i;
    }
}

//清除所有打钩
void setting_setmm::clear_checkboxes(){
    QMap<QString, QCheckBox*>::const_iterator i = contracts.constBegin();
    while (i != contracts.constEnd()) {
        i.value()->setChecked(false);
        ++i;
    }
}
