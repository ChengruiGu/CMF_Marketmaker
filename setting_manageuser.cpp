#include "setting_manageuser.h"
#include "ui_setting_manageuser.h"
#include "setting_createrole.h"
#include "setting_resetpwd.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QtSql>

setting_manageuser::setting_manageuser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting_manageuser)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database();

    //model连接数据库
    model = new QSqlRelationalTableModel(this, db);
    model->setTable("users");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //输入数据库数据
    model->select();

    //改下标题
    model->setHeaderData(0,Qt::Horizontal, "用户名");
    model->setHeaderData(1,Qt::Horizontal, "姓名");
    model->setHeaderData(2,Qt::Horizontal, "角色");
    model->setHeaderData(3,Qt::Horizontal, "电话");
    model->setHeaderData(4,Qt::Horizontal, "邮箱");
    model->setHeaderData(5,Qt::Horizontal, "创建时间");

    //model连接view, 显示数据, 调整显示拉伸
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
}

setting_manageuser::~setting_manageuser()
{
    delete ui;
}

void setting_manageuser::on_pushButton_2_released()
{
    setting_resetPwd *rp = new setting_resetPwd(this);
    rp->exec();
}

void setting_manageuser::on_pushButton_released()
{
    setting_createRole *cr = new setting_createRole();
    cr->exec();
    model->select(); //刷新页面
}

/*删除用户*/
void setting_manageuser::on_pushButton_3_released()
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

/*点击选中*/
void setting_manageuser::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    row_to_delete = row;
}
