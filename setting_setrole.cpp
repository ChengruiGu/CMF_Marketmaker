#include "setting_setrole.h"
#include "ui_setting_setrole.h"
#include <QStandardItemModel>

setting_setrole::setting_setrole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_setrole)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(this);

    model->setColumnCount(1);
    model->setItem(0, 0, new QStandardItem("管理员"));
    model->setItem(1, 0, new QStandardItem("交易员"));
    model->setItem(2, 0, new QStandardItem("风控员"));
    model->setItem(3, 0, new QStandardItem("IT"));
    ui->listView->setModel(model);
}

setting_setrole::~setting_setrole()
{
    delete ui;
}
