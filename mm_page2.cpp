#include "mm_page2.h"
#include "ui_mm_page2.h"

mm_page2::mm_page2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_page2)
{
    ui->setupUi(this);
}

mm_page2::~mm_page2()
{
    delete ui;
}
