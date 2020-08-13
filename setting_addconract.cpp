#include "setting_addconract.h"
#include "ui_setting_addconract.h"
#include <QStandardItemModel>

setting_addconract::setting_addconract(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_addconract)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(this);

    model->setColumnCount(1);
    model->setItem(0, 0, new QStandardItem("MA009"));
    model->setItem(1, 0, new QStandardItem("CU2008"));
    model->setItem(2, 0, new QStandardItem("AU2010"));
    model->setItem(3, 0, new QStandardItem("IH2009"));
    ui->tableView->setModel(model);
}

setting_addconract::~setting_addconract()
{
    delete ui;
}
