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
    ui->horizontalLayout_9->setContentsMargins(1,1,1,1);
    ui->horizontalLayout_9->addWidget(b);
    ui->horizontalLayout_9->addWidget(b1);

}

mm_page::~mm_page()
{
    delete ui;
}
