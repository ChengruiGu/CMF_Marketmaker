#include "mm_page.h"
#include "ui_mm_page.h"
#include "bar.h"
#include <QtWidgets>

mm_page::mm_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_page)
{
    ui->setupUi(this);

    bar *b = new bar;
    bar1 *b1 = new bar1;
//    QHBoxLayout *hbox = new QHBoxLayout;
//    hbox->addWidget(b);
//    hbox->addWidget(b1);
//    QGroupBox *statBox = new QGroupBox;
//    statBox->setLayout(hbox);
//    //ui->barhLayout_6->addWidget(statWidget);
//    ui->topFormLayout->addWidget(statBox);
    //ui->statbox->setContentsMargins(1,1,1,1);
    ui->horizontalLayout_8->setContentsMargins(1,1,1,1);
    ui->horizontalLayout_8->addWidget(b);
    ui->horizontalLayout_8->addWidget(b1);

}

mm_page::~mm_page()
{
    delete ui;
}

void mm_page::setName(QString s){
    ui->label_18->setText(s);
}
