#include "setting_riskctrl.h"
#include "ui_setting_riskctrl.h"
#include <QStandardItemModel>

setting_riskctrl::setting_riskctrl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_riskctrl)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);

    model->setColumnCount(1);
    model->setItem(0, 0, new QStandardItem("cu2009"));
    model->setItem(1, 0, new QStandardItem("MA009"));
    model->setItem(2, 0, new QStandardItem("au2010"));
    model->setItem(3, 0, new QStandardItem("WH2010"));
    ui->listView->setModel(model);
    connect(this->ui->listView,&QListView::clicked,this,&setting_riskctrl::setContract);

}

setting_riskctrl::~setting_riskctrl()
{
    delete ui;
}

void setting_riskctrl::setContract(QModelIndex qi){
    QString s = qi.data().toString();
    ui->label_4->setText(s);
}
