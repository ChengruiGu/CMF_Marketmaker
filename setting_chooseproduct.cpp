#include "setting_chooseproduct.h"
#include "ui_setting_chooseproduct.h"

setting_chooseProduct::setting_chooseProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_chooseProduct)
{
    ui->setupUi(this);
}

setting_chooseProduct::~setting_chooseProduct()
{
    delete ui;
}
