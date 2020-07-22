#include "setting_uploadstrategy.h"
#include "ui_setting_uploadstrategy.h"

#include <QFileDialog>

setting_uploadstrategy::setting_uploadstrategy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_uploadstrategy)
{
    ui->setupUi(this);
}

setting_uploadstrategy::~setting_uploadstrategy()
{
    delete ui;
}

void setting_uploadstrategy::on_pushButton_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    ui->label_2->setText(file_name);
}
