#include "setting_riskctrlfold.h"
#include "ui_setting_riskctrlfold.h"
#include "setting_riskctrl.h"
#include "setting_riskctrlcategory.h"
#include "setting_riskctrlp.h"
#include "setting_riskctrlproduct.h"

setting_riskctrlfold::setting_riskctrlfold(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting_riskctrlfold), v1(1), v2(1), v3(1), v4(1)
{
    ui->setupUi(this);
    dhy = new setting_riskctrl;
    pz = new setting_riskctrlproduct;
    pl = new setting_riskctrlcategory;
    zh = new setting_riskctrlp;
    ui->verticalLayout->addWidget(dhy);
    ui->verticalLayout->addStretch();
    ui->verticalLayout_2->addWidget(pz);
    ui->verticalLayout_2->addStretch();
    ui->verticalLayout_3->addWidget(pl);
    ui->verticalLayout_3->addStretch();
    ui->verticalLayout_4->addWidget(zh);
    ui->verticalLayout_4->addStretch();
    dhy->setVisible(true);
    pz->setVisible(true);
    pl->setVisible(true);
    zh->setVisible(true);
    connect(ui->pushButton,&QPushButton::clicked,this,&setting_riskctrlfold::setdhy);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&setting_riskctrlfold::setpz);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&setting_riskctrlfold::setpl);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&setting_riskctrlfold::setzh);
}

setting_riskctrlfold::~setting_riskctrlfold()
{
    delete ui;
    delete dhy;
    delete pz;
    delete pl;
    delete zh;
}

void setting_riskctrlfold::setdhy(){
    ++v1;
    if(v1 & 1){
        dhy->setVisible(true);
    } else {
        dhy->setVisible(false);
    }
    //this->showMinimized();
}

void setting_riskctrlfold::setpz(){
    ++v2;
    if(v2 & 1){
        pz->setVisible(true);
    } else {
        pz->setVisible(false);
    }
    //this->showMinimized();
}

void setting_riskctrlfold::setpl(){
    ++v3;
    if(v3 & 1){
        pl->setVisible(true);
    } else {
        pl->setVisible(false);
    }
    //this->showMinimized();
}

void setting_riskctrlfold::setzh(){
    ++v4;
    if(v4 & 1){
        zh->setVisible(true);
    } else {
        zh->setVisible(false);
    }
    //this->showMinimized();
}
