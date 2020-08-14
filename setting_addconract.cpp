#include "setting_addconract.h"
#include "ui_setting_addconract.h"
#include <QStandardItemModel>


setting_addconract::setting_addconract(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_addconract)
{
    ui->setupUi(this);
        //获取数据库连接
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery sql_query;

        sql_query.exec("PRAGMA foreign_keys = ON");

        //model连接数据库
        model = new QSqlRelationalTableModel(this, db);
        model->setTable("future_contracts");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        //输入数据库数据
        if(!model->select()){
            qWarning("model not selcted");
        }

        //改下标题
        model->setHeaderData(0,Qt::Horizontal, "合约代码");
        model->setHeaderData(1,Qt::Horizontal, "品种代码");
        model->setHeaderData(2,Qt::Horizontal, "交易所");

        //model连接view, 显示数据, 调整显示拉伸
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //禁用编辑
        ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
}

setting_addconract::~setting_addconract()
{
    delete ui;
}
