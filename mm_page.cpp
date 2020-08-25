#include "mm_page.h"
#include "ui_mm_page.h"
#include "bar.h"
#include "mm_tradecontrol.h"
#include <QtWidgets>
#include <QProcess>
#include <QDir>

mm_page::mm_page(QString username, QString future_name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_page)
{
    ui->setupUi(this);
    this->username = username;
    ui->label_18->setText(future_name);

    //画右下方3个柱状图
    bar *b = new bar;
    bar1 *b1 = new bar1;
    bar2 *b2 = new bar2;
    ui->horizontalLayout_8->setContentsMargins(1,1,1,1);
    ui->horizontalLayout_8->addWidget(b);
    ui->horizontalLayout_8->addWidget(b1);
    ui->horizontalLayout_8->addWidget(b2);


    QSqlQuery sql_query;

    sql_query.prepare("SELECT future_code FROM futures WHERE future_name = :future_name");
    sql_query.bindValue(":future_name", ui->label_18->text());
    if(!sql_query.exec()) qDebug() << sql_query.lastError();
    QString future_code;
    while(sql_query.next()){
        future_code = sql_query.value(0).toString();
    }

    sql_query.prepare("SELECT user_contracts.contract_code "
                      "FROM user_contracts "
                      "WHERE user_contracts.username = :username "
                      "AND user_contracts.contract_code IN "
                      "(SELECT contract_code FROM future_contracts WHERE future_code = :future_code) "
                      );
    sql_query.bindValue(":username", this->username);
    sql_query.bindValue(":future_code", future_code);

    if(!sql_query.exec()) qDebug() << sql_query.lastError();

    while(sql_query.next()){
        QString contract_code = sql_query.value(0).toString();
        contracts.push_back(contract_code);
    }
    QVector<QString>::const_iterator i = contracts.constBegin();
    while(i != contracts.constEnd()){
        sql_query.prepare("SELECT strategy_name FROM strategy_contracts WHERE contract_code = :contract_code");
        sql_query.bindValue(":contract_code", *i);
        sql_query.exec();
        QStringList strategyList;
        while(sql_query.next()){
            QString strategy = sql_query.value(0).toString();
            strategyList.push_back(strategy);
        }
        mm_tradecontrol *tc = new mm_tradecontrol(*i, ui->plainTextEdit, strategyList);
        trade_controls.push_back(tc);
        ui->verticalLayout_7->addWidget(tc);
        ++i;
    }

}

mm_page::~mm_page()
{
    delete ui;
}

void mm_page::setName(QString s){
    ui->label_18->setText(s);
    ui->label_56->setText("期货");
}

void mm_page::setName1(QString s){
    ui->label_18->setText(s);
    ui->label_56->setText("期权");
}

void mm_page::refreshStrategyList(){

}

//全部启动
void mm_page::on_pushButton_released()
{
    for(int i = 0; i < trade_controls.length(); ++i){
        trade_controls[i]->start_trading();
    }
}

//全部停止
void mm_page::on_pushButton_2_released()
{
    for(int i = 0; i < trade_controls.length(); ++i){
        trade_controls[i]->suspend_trading();
    }
}

void mm_page::on_mm_page_destroyed()
{
    on_pushButton_2_released();
}
