#include "twolabel.h"
#include "ui_twolabel.h"

twoLabel::twoLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::twoLabel)
{
    ui->setupUi(this);
}

twoLabel::~twoLabel()
{
    delete ui;
}

void twoLabel::setLabel1(QString s){
    ui->label->setText(s);
}

void twoLabel::setLabel2(QString s){
    ui->label_2->setText(s);
}
