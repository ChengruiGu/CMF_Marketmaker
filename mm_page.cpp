#include "mm_page.h"
#include "ui_mm_page.h"
#include "bar.h"
#include <QtWidgets>
#include <QProcess>

mm_page::mm_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_page)
{
    ui->setupUi(this);

    bar *b = new bar;
    bar1 *b1 = new bar1;
    bar2 *b2 = new bar2;
    ui->horizontalLayout_8->setContentsMargins(1,1,1,1);
    ui->horizontalLayout_8->addWidget(b);
    ui->horizontalLayout_8->addWidget(b1);
    ui->horizontalLayout_8->addWidget(b2);
}

mm_page::~mm_page()
{
    delete ui;
}

void mm_page::setName(QString s){
    ui->label_18->setText(s);
    ui->label_56->setText("期货");
}

void mm_page::setName1(QString s){
    ui->label_18->setText(s);
    ui->label_56->setText("期权");
}

void mm_page::on_pushButton_3_released()
{
    if(p1_state) return;

    //创建进程
       QString program = "D:\\a\\Debug\\a.exe";
       QStringList arguments;
       arguments << "2020年8月5日" << "星期二";

       p1 = new QProcess(this);
       //connect要放在这里 不然会nullptr exception
       connect(p1,&QProcess::readyReadStandardOutput,this,&mm_page::on_p1_ReadStdOutput);
       p1->start(program, arguments);
       p1_state = 1;

       //运行状态标签
       ui->label_61->setText("运行中");
       ui->label_61->setStyleSheet("QLabel {color : red; }");
}

void mm_page::on_p1_started(){

}

void mm_page::on_p1_ReadStdOutput(){
    char buf[1024];
    qint64 lineLength = p1->readLine(buf, sizeof(buf));
        if (lineLength != -1) {
            QString s = QString::fromLocal8Bit(buf);
            ui->plainTextEdit->appendPlainText(s);
        }
}

void mm_page::on_pushButton_4_released()
{
    if(!p1_state) return;
    p1->kill();
    p1_state = 0;

    ui->label_61->setText("已暂停");
    ui->label_61->setStyleSheet("QLabel {color : blue; }");
}
