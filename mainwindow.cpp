#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("��֤�ʱ�Ͷ�����޹�˾����ϵͳ"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

