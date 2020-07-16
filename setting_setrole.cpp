#include "setting_setrole.h"
#include "ui_setting_setrole.h"

setting_setrole::setting_setrole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_setrole)
{
    ui->setupUi(this);
}

setting_setrole::~setting_setrole()
{
    delete ui;
}
