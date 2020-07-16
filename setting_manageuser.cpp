#include "setting_manageuser.h"
#include "ui_setting_manageuser.h"
#include "setting_createrole.h"
#include "setting_resetpwd.h"

#include <QTableView>
#include <QStandardItemModel>

setting_manageuser::setting_manageuser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting_manageuser)
{
    ui->setupUi(this);

    QStandardItemModel* model = new QStandardItemModel(this);

    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal, "用户名");
    model->setHeaderData(1,Qt::Horizontal, "姓名");
    model->setHeaderData(2,Qt::Horizontal, "角色");
    model->setHeaderData(3,Qt::Horizontal, "电话");
    model->setHeaderData(4,Qt::Horizontal, "创建时间");

    model->setItem(0, 0, new QStandardItem("cg487"));
    model->setItem(0, 1, new QStandardItem("顾成睿"));
    model->setItem(0, 2, new QStandardItem("IT"));
    model->setItem(0, 3, new QStandardItem("13570808796"));
    model->setItem(0, 4, new QStandardItem("2020-7-16"));

    model->setItem(1, 0, new QStandardItem("dl335"));
    model->setItem(1, 1, new QStandardItem("林立东"));
    model->setItem(1, 2, new QStandardItem("管理员"));
    model->setItem(1, 3, new QStandardItem("13312341234"));
    model->setItem(1, 4, new QStandardItem("2020-7-16"));

    model->setItem(2, 0, new QStandardItem("ch761"));
    model->setItem(2, 1, new QStandardItem("何川"));
    model->setItem(2, 2, new QStandardItem("交易员"));
    model->setItem(2, 3, new QStandardItem("13343214321"));
    model->setItem(2, 4, new QStandardItem("2020-7-17"));

    model->setItem(3, 0, new QStandardItem("jq190"));
    model->setItem(3, 1, new QStandardItem("覃嘉俊"));
    model->setItem(3, 2, new QStandardItem("风控员"));
    model->setItem(3, 3, new QStandardItem("13354325432"));
    model->setItem(3, 4, new QStandardItem("2020-7-18"));

    ui->tableView->setModel(model);
}

setting_manageuser::~setting_manageuser()
{
    delete ui;
}

void setting_manageuser::on_pushButton_2_released()
{
    setting_resetPwd *rp = new setting_resetPwd;
    rp->show();
}

void setting_manageuser::on_pushButton_released()
{
    setting_createRole *cr = new setting_createRole;
    cr->show();
}
