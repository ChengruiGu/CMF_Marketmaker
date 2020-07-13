#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mm_page.h"
#include "mm_page2.h"
#include "future_mm.h"
#include "setting_createrole.h"
#include "setting_resetpwd.h"
#include "setting_chooseproduct.h"
#include "setting_setmm.h"
#include "setting_riskctrl.h"
#include "setting_changepwd.h"
#include "setting_riskprmt.h"



#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("招证资本投资有限公司做市系统"));

    pagesWidget = new QStackedWidget;
    //pagesWidget->setWindowTitle("pagesWidget");
    future_page = new mm_page;
    pagesWidget->addWidget(future_page);
    pagesWidget->addWidget(new mm_page2);

    setCentralWidget(pagesWidget);

    connect(this->ui->actiontong_2,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionlv_2,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionxi_2,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionnie_2,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionqian,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjin,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionyin,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionluowen,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionxiancai,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionbuxiugang,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionrejuan,&QAction::triggered,this,&MainWindow::setFuturePage);

    connect(this->ui->actiontong_op,&QAction::triggered,this,&MainWindow::setOptionPage);

    connect(this->ui->actioncjyh,&QAction::triggered,this,&MainWindow::createRole);
    connect(this->ui->actionmmcz,&QAction::triggered,this,&MainWindow::resetPwd);
    connect(this->ui->actionpzsz,&QAction::triggered,this,&MainWindow::chooseProduct);
    connect(this->ui->actionzssz,&QAction::triggered,this,&MainWindow::setMm);
    connect(this->ui->actionfksz,&QAction::triggered,this,&MainWindow::riskControl);
    connect(this->ui->actionmmxg,&QAction::triggered,this,&MainWindow::changePwd);
    connect(this->ui->actionjkzb,&QAction::triggered,this,&MainWindow::riskParameter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFuturePage(){
    pagesWidget->setCurrentIndex(0); //mm_page
    QAction *a = qobject_cast<QAction*>(sender());
    QString s = a->text();
    future_page->setName(s);
}

void MainWindow::setOptionPage(){
    pagesWidget->setCurrentIndex(1);
}

void MainWindow::createRole(){
    setting_createRole *cr = new setting_createRole;
    cr->show();
}

void MainWindow::resetPwd(){
    setting_resetPwd *rp = new setting_resetPwd;
    rp->show();
}

void MainWindow::chooseProduct(){
    setting_chooseProduct *cp = new setting_chooseProduct;
    cp->show();
}

void MainWindow::setMm(){
    setting_setmm *sm = new setting_setmm;
    sm->show();
}

void MainWindow::riskControl(){
    setting_riskctrl *rc = new setting_riskctrl;
    rc->show();
}

void MainWindow::changePwd(){
    setting_changepwd *cp = new setting_changepwd;
    cp->show();
}

void MainWindow::riskParameter(){
    setting_riskprmt *rp = new setting_riskprmt;
    rp->show();
}
