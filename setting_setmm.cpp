#include "setting_setmm.h"
#include "ui_setting_setmm.h"
#include <QStandardItemModel>

setting_setmm::setting_setmm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_setmm)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(this);

    model->setColumnCount(1);
    model->setItem(0, 0, new QStandardItem("cg487"));
    ui->listView->setModel(model);
}

setting_setmm::~setting_setmm()
{
    delete ui;
}
