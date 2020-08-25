#include "setting_chooseproduct.h"
#include "ui_setting_chooseproduct.h"

setting_chooseProduct::setting_chooseProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_chooseProduct)
{
    ui->setupUi(this);

    //获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    //model连接数据库
    model = new QSqlRelationalTableModel(this, db);
    model->setTable("futures"); //选择要读的表格
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //当调用model->submitAll()时才同步数据库
    model->select(); //从数据库中读取数据

    //改下标题
    model->setHeaderData(0,Qt::Horizontal, "品种名称");
    model->setHeaderData(1,Qt::Horizontal, "交易代码");
    model->setHeaderData(2,Qt::Horizontal, "交易所");
    model->setHeaderData(3,Qt::Horizontal, "品种类别");
    model->setHeaderData(4,Qt::Horizontal, "合约乘数");
    model->setHeaderData(5,Qt::Horizontal, "最小变动价位");

    //model连接view, 显示数据, 调整显示拉伸
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //禁用编辑
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
}

setting_chooseProduct::~setting_chooseProduct()
{
    delete ui;
}

void setting_chooseProduct::on_pushButton_released()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.open()) {
        qWarning("cannot open db in createrole");
        return;
    }

    //去掉空格
    QString name = ui->lineEdit->text();
    name.replace(QString(" "),QString(""));

    QString code = ui->lineEdit_2->text();
    code.replace(QString(" "),QString(""));

    QString multiplier = ui->lineEdit_3->text();
    multiplier.replace(QString(" "),QString(""));

    QString mpf = ui->lineEdit_4->text();
    mpf.replace(QString(" "),QString(""));

    QString exchange = ui->comboBox->currentText();
    QString category = ui->comboBox_2->currentText();


    if(name.isEmpty() || code.isEmpty() || multiplier.isEmpty() || mpf.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("输入不能为空！");
        msgBox.exec();
        return;
    }

    QSqlRecord record;
    record.append(QSqlField("future_name"));
    record.append(QSqlField("future_code"));
    record.append(QSqlField("exchange"));
    record.append(QSqlField("category"));
    record.append(QSqlField("multiplier"));
    record.append(QSqlField("mpf"));

    record.setValue("future_name", name);
    record.setValue("future_code", code);
    record.setValue("exchange", exchange);
    record.setValue("category", category);
    record.setValue("multiplier", multiplier.toInt());
    record.setValue("mpf", mpf);

    model->insertRecord(-1, record); //插入record
    model->submitAll(); //跟数据库同步
    model->select(); //刷新Model
}

void setting_chooseProduct::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    row_to_delete = row;
    QSqlRecord record = model->record(row);
    ui->lineEdit->setText(record.value(0).toString());
    ui->lineEdit_2->setText(record.value(1).toString());
    ui->comboBox->setCurrentText(record.value(2).toString());
    ui->comboBox_2->setCurrentText(record.value(3).toString());
    ui->lineEdit_3->setText(record.value(4).toString());
    ui->lineEdit_4->setText(record.value(5).toString());

}

void setting_chooseProduct::on_pushButton_2_released()
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
