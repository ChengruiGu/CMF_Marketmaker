#include "setting_addconract.h"
#include "ui_setting_addconract.h"
#include <QStandardItemModel>
#include <QMessageBox>


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

        on_comboBox_currentTextChanged(ui->comboBox->currentText());

        //禁用编辑
        ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
}

setting_addconract::~setting_addconract()
{
    delete ui;
}

/*交易所对应品种*/
void setting_addconract::on_comboBox_currentTextChanged(const QString &arg1)
{
    //获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery sql_query;

    sql_query.prepare("SELECT future_code FROM futures WHERE exchange = :exchange");
    sql_query.bindValue(":exchange", arg1);

    if(!sql_query.exec()) {
        qDebug() << "Select failed!";
        qDebug() << sql_query.lastError();
        return;
    }

    ui->comboBox_2->clear();
    QStringList name_list;

    while(sql_query.next()){
        QString future_name = sql_query.value(0).toString();
        name_list << future_name;
    }
    ui->comboBox_2->addItems(name_list);

}

/*添加合约*/
void setting_addconract::on_pushButton_released()
{
    QString contract_code = ui->lineEdit->text();
    contract_code.replace(" ", "");
    if(contract_code.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("输入不能为空！");
        msgBox.exec();
        return;
    }

    QSqlRecord record;
    record.append(QSqlField("contract_code"));
    record.append(QSqlField("exchange"));
    record.append(QSqlField("future_code"));

    record.setValue("contract_code", contract_code);
    record.setValue("exchange", ui->comboBox->currentText());
    record.setValue("future_code", ui->comboBox_2->currentText());

    model->insertRecord(-1, record); //插入record
    model->submitAll(); //跟数据库同步
    model->select(); //刷新Model
}

/*删除*/
void setting_addconract::on_pushButton_2_released()
{
    if(row_to_delete != -1){
        //qDebug() <<
        (model->removeRow(row_to_delete));
        //qDebug() <<
        (model->submitAll());
        //qDebug() <<
        (model->select());
        row_to_delete = -1;
    }
}

/*选中列表*/
void setting_addconract::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    row_to_delete = row;
    QSqlRecord record = model->record(row);
    ui->lineEdit->setText(record.value(0).toString());
    ui->comboBox->setCurrentText(record.value(2).toString());
}
