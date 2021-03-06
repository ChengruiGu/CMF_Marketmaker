#include "setting_uploadstrategy.h"
#include "ui_setting_uploadstrategy.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

setting_uploadstrategy::setting_uploadstrategy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_uploadstrategy)
{
    ui->setupUi(this);
    //获取数据库连接
    QSqlDatabase db = QSqlDatabase::database();

    //model连接数据库
    model = new QSqlRelationalTableModel(this, db);
    model->setTable("strategies");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //输入数据库数据
    model->select();

    //改下标题
    model->setHeaderData(0,Qt::Horizontal, "策略名");

    //model连接view, 显示数据, 调整显示拉伸
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //禁用编辑
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);

    //创建checkboxes
    QSqlQuery sql_query;
    sql_query.exec("SELECT contract_code FROM future_contracts");
    while(sql_query.next()){
        QString name = sql_query.value(0).toString();
        //qDebug() << name;
        QCheckBox* cb = new QCheckBox(name);
        contracts[name] = cb;
        ui->gridLayout->addWidget(cb);
    }

    //model_2连接数据库
    model_2 = new QSqlRelationalTableModel(this, db);
    model_2->setTable("parameters");
    model_2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //输入数据库数据
    model_2->select();

    //改下标题
    model_2->setHeaderData(0,Qt::Horizontal, "参数名");

    //model连接view, 显示数据, 调整显示拉伸
    ui->tableView_2->setModel(model_2);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //禁用编辑
    ui->tableView_2->setEditTriggers(QTableView::NoEditTriggers);

    //创建checkboxes
    sql_query.exec("SELECT strategy_name FROM strategies");
    while(sql_query.next()){
        QString name = sql_query.value(0).toString();
        //qDebug() << name;
        QCheckBox* cb = new QCheckBox(name);
        strategies[name] = cb;
        ui->gridLayout_2->addWidget(cb);
    }

}

setting_uploadstrategy::~setting_uploadstrategy()
{
    delete ui;
}

/*上传文件按钮*/
void setting_uploadstrategy::on_pushButton_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题","/","(*.exe)");
    //QFileDialog是windows的上传文件界面，用法参考doc
    ui->label_2->setText(file_name);
}

/* 复制上传的策略到/strategies文件夹内
 * 该方法参考http://qiusuoge.com/12051.html*/
void setting_uploadstrategy::on_pushButton_2_released()
{
    QString src_path = ui->label_2->text();
    if(src_path == "Not Selected"){
        QMessageBox msgBox;
        msgBox.setText("请先选择要上传的策略！");
        msgBox.exec();
        return;
    }

    QString strategy_name = ui->lineEdit->text(); //获取策略名称
    strategy_name.replace(QString(" "),QString("")); //替换所有空格
    if(strategy_name == ""){
        QMessageBox msgBox;
        msgBox.setText("策略名不能为空！");
        msgBox.exec();
        return;
    }

    src_path.replace("\\","/"); //调整路径格式
    QString dest("./strategies/");
    dest.append(strategy_name);
    dest.append(".exe");

    QDir *createfile = new QDir;
    bool exist = createfile->exists(dest);
    if (exist){
        QMessageBox msgBox;
        msgBox.setText("同名策略已存在，是否替换？");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            createfile->remove(dest);
        } else {
            return;
        }
    }

    if(!QFile::copy(src_path, dest)) //拷贝文件
    {
        qWarning("copy strategy failed!!!");
        return;
    }

    QSqlQuery sql_query; //更新数据库
    sql_query.prepare("INSERT INTO strategies VALUES(:strategy_name)");
    sql_query.bindValue(":strategy_name", strategy_name);
    sql_query.exec();

    QMessageBox msgBox;
    msgBox.setText("上传成功");
    msgBox.exec();
    ui->label_2->clear();
    model->select();
    QCheckBox* cb = new QCheckBox(strategy_name);
    strategies[strategy_name] = cb;
    ui->gridLayout_2->addWidget(cb);
}

/* 点击策略列表 */
void setting_uploadstrategy::on_tableView_clicked(const QModelIndex &index)
{
    QString strategy_name = model->data(index).toString();
    ui->label_8->setText(strategy_name);
    QSqlQuery sql_query;
    sql_query.prepare("SELECT contract_code "
                      "FROM strategy_contracts "
                      "WHERE strategy_name = :strategy_name");
    sql_query.bindValue(":strategy_name",strategy_name);

    if(!sql_query.exec()) qDebug() << sql_query.lastError();
    clear_checkboxes();
    while(sql_query.next()){
        QString contract_code = sql_query.value(0).toString();
        //qDebug() << contract_code;
        contracts[contract_code]->setChecked(true);
    }
}

/*更新策略对应合约*/
void setting_uploadstrategy::on_pushButton_5_released()
{
    QString strategy_name = ui->label_8->text();
    if(strategy_name.isEmpty()) return;
    QSqlQuery sql_query;
    QMap<QString, QCheckBox*>::const_iterator i = contracts.constBegin();
    while (i != contracts.constEnd()) {
        if(i.value()->isChecked()){ //如果被打钩则添加
            sql_query.prepare("INSERT INTO strategy_contracts VALUES(:strategy_name, :contract_code)");
            sql_query.bindValue(":strategy_name", strategy_name);
            sql_query.bindValue(":contract_code", i.value()->text());
            sql_query.exec();
        } else { //如果没被打钩则删除权限
            sql_query.prepare("DELETE FROM strategy_contracts "
                              "WHERE strategy_name = :strategy_name AND contract_code = :contract_code");
            sql_query.bindValue(":strategy_name", strategy_name);
            sql_query.bindValue(":contract_code", i.value()->text());
            sql_query.exec();
        }
        ++i;
    }
}

void setting_uploadstrategy::clear_checkboxes(){
    QMap<QString, QCheckBox*>::const_iterator i = contracts.constBegin();
    while (i != contracts.constEnd()) {
        i.value()->setChecked(false);
        ++i;
    }
}

/*删除策略*/
void setting_uploadstrategy::on_pushButton_6_released()
{
    QString strategy_name = ui->label_8->text();
    if(strategy_name.isEmpty()) return;

    QMessageBox msgBox;
    msgBox.setText("确认删除此策略吗？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        QSqlQuery sql_query;
        sql_query.prepare("DELETE FROM strategies WHERE strategy_name = :strategy_name");
        sql_query.bindValue(":strategy_name",strategy_name);
        sql_query.exec();

        QString dest("./strategies/");
        dest.append(strategy_name);
        dest.append(".exe");
        QDir *createfile = new QDir;
        createfile->remove(dest);

        model->select();
        ui->label_8->clear();
        delete(strategies[strategy_name]); //删除时会自动通知ui->grid_layout_2删除对应的checkbox显示
        strategies.remove(strategy_name);
    } else {
        return;
    }
}

/* 点击参数列表 */
void setting_uploadstrategy::on_tableView_2_clicked(const QModelIndex &index)
{
    QString parameter_name = model_2->data(index).toString();
    ui->label_10->setText(parameter_name);
    QSqlQuery sql_query;
    sql_query.prepare("SELECT strategy_name "
                      "FROM parameter_strategies "
                      "WHERE parameter_name = :parameter_name");
    sql_query.bindValue(":parameter_name",parameter_name);

    if(!sql_query.exec()) qDebug() << sql_query.lastError();
    clear_checkboxes_2();
    while(sql_query.next()){
        QString strategy_name = sql_query.value(0).toString();
        //qDebug() << contract_code;
        strategies[strategy_name]->setChecked(true);
    }
}

void setting_uploadstrategy::clear_checkboxes_2(){
    QMap<QString, QCheckBox*>::const_iterator i = strategies.constBegin();
    while (i != strategies.constEnd()) {
        i.value()->setChecked(false);
        ++i;
    }
}

/* 点击上传参数 */
void setting_uploadstrategy::on_pushButton_3_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题","/","(*.txt)");
    //QFileDialog是windows的上传文件界面，用法参考doc
    ui->label_5->setText(file_name);
}

/* 点击确认上传参数 */
void setting_uploadstrategy::on_pushButton_4_released()
{
    QString src_path = ui->label_5->text();
    if(src_path == "Not Selected"){
        QMessageBox msgBox;
        msgBox.setText("请先选择要上传的策略！");
        msgBox.exec();
        return;
    }

    QString parameter_name = ui->lineEdit_2->text(); //获取策略名称
    parameter_name.replace(QString(" "),QString("")); //替换所有空格
    if(parameter_name == ""){
        QMessageBox msgBox;
        msgBox.setText("参数名不能为空！");
        msgBox.exec();
        return;
    }

    src_path.replace("\\","/"); //调整路径格式
    QString dest("./parameters/");
    dest.append(parameter_name);
    dest.append(".txt");
//    qDebug() << dest;
//    qDebug() << src_path;

    QDir *createfile = new QDir;
    bool exist = createfile->exists(dest);
    if (exist){
        QMessageBox msgBox;
        msgBox.setText("同名参数已存在，是否替换？");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            createfile->remove(dest);
        } else {
            return;
        }
    }

    if(!QFile::copy(src_path, dest)) //拷贝文件
    {
        qWarning("copy parameter failed!!!");
        return;
    }

    QSqlQuery sql_query; //更新数据库
    sql_query.prepare("INSERT INTO parameters VALUES(:parameter_name)");
    sql_query.bindValue(":parameter_name", parameter_name);
    sql_query.exec();

    QMessageBox msgBox;
    msgBox.setText("上传成功");
    msgBox.exec();
    ui->label_5->clear();
    model_2->select();
}

/* 点击确认参数对应策略 */
void setting_uploadstrategy::on_pushButton_7_released()
{
    QString parameter_name = ui->label_10->text();
    if(parameter_name.isEmpty()) return;
    QSqlQuery sql_query;
    QMap<QString, QCheckBox*>::const_iterator i = strategies.constBegin();
    while (i != strategies.constEnd()) {
        if(i.value()->isChecked()){ //如果被打钩则添加
            sql_query.prepare("INSERT INTO parameter_strategies VALUES(:parameter_name, :strategy_name)");
            sql_query.bindValue(":parameter_name", parameter_name);
            sql_query.bindValue(":strategy_name", i.value()->text());
            sql_query.exec();
        } else { //如果没被打钩则删除权限
            sql_query.prepare("DELETE FROM parameter_strategies "
                              "WHERE parameter_name = :parameter_name AND strategy_name = :strategy_name");
            sql_query.bindValue(":parameter_name", parameter_name);
            sql_query.bindValue(":strategy_name", i.value()->text());
            sql_query.exec();
        }
        ++i;
    }
}

/* 点击删除参数 */
void setting_uploadstrategy::on_pushButton_8_released()
{
    QString parameter_name = ui->label_10->text();
    if(parameter_name.isEmpty()) return;

    QMessageBox msgBox;
    msgBox.setText("确认删除此参数吗？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        QSqlQuery sql_query;
        sql_query.prepare("DELETE FROM parameters WHERE parameter_name = :parameter_name");
        sql_query.bindValue(":parameter_name",parameter_name);
        sql_query.exec();

        QString dest("./parameters/");
        dest.append(parameter_name);
        dest.append(".txt");
        QDir *createfile = new QDir;
        createfile->remove(dest);
        model_2->select();
        ui->label_10->clear();
    } else {
        return;
    }
}
