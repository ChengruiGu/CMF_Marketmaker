#include "setting_riskctrlproduct.h"
#include "ui_setting_riskctrlproduct.h"
#include <QStandardItemModel>

setting_riskctrlproduct::setting_riskctrlproduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_riskctrlproduct)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);

    model->setColumnCount(1);
    model->setItem(0, 0, new QStandardItem("铜"));
    model->setItem(1, 0, new QStandardItem("甲醇"));
    model->setItem(2, 0, new QStandardItem("金"));
    model->setItem(3, 0, new QStandardItem("天然橡胶"));
    ui->listView->setModel(model);
    connect(this->ui->listView,&QListView::clicked,this,&setting_riskctrlproduct::setProduct);
}

setting_riskctrlproduct::~setting_riskctrlproduct()
{
    delete ui;
}

void setting_riskctrlproduct::setProduct(QModelIndex qi){
    QString s = qi.data().toString();
    ui->label_5->setText(s);
}
