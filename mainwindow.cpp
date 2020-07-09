#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mm_page.h"
#include "mm_page2.h"
#include "future_mm.h"
#include "setting_createrole.h"
#include "setting_resetpwd.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("招证资本投资有限公司做市系统"));

    pagesWidget = new QStackedWidget;
    //pagesWidget->setWindowTitle("pagesWidget");
    pagesWidget->addWidget(new mm_page);
    pagesWidget->addWidget(new mm_page2);

    setCentralWidget(pagesWidget);

    connect(this->ui->actionsqs,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionsqs_2,&QAction::triggered,this,&MainWindow::setOptionPage);

    connect(this->ui->actioncjyh,&QAction::triggered,this,&MainWindow::createRole);
    connect(this->ui->actionmmcz,&QAction::triggered,this,&MainWindow::resetPwd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFuturePage(){
    pagesWidget->setCurrentIndex(0); //mm_page
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
