#include "mm_page.h"
#include "ui_mm_page.h"
#include "bar.h"
#include <QtWidgets>
#include <QProcess>
#include <QDir>

mm_page::mm_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_page)
{
    ui->setupUi(this);

    //画右下方3个柱状图
    bar *b = new bar;
    bar1 *b1 = new bar1;
    bar2 *b2 = new bar2;
    ui->horizontalLayout_8->setContentsMargins(1,1,1,1);
    ui->horizontalLayout_8->addWidget(b);
    ui->horizontalLayout_8->addWidget(b1);
    ui->horizontalLayout_8->addWidget(b2);

    //获取策略并显示在策略启动栏的combobox上
    refreshStrategyList();

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

void mm_page::refreshStrategyList(){
    //获取策略并显示在策略启动栏的combobox上
    ui->comboBox_3->clear();
    QDir strategyDir(QString("./strategies"));
    QStringList strategyList = strategyDir.entryList();
    for(int i = 2; i < strategyList.length(); ++i){
        QDir strategyName(strategyList[i]);
        ui->comboBox_3->addItem(strategyName.dirName());
    }
}

void mm_page::on_pushButton_3_released()
{
    if(p1_state) return;

    //创建进程
       QString program = "./strategies/";
       program.append(p1_strategy);
       QDir strategyPath(program);

       QStringList arguments;
       //arguments << "2020年8月5日" << "星期二";

       p1 = new QProcess(this);
       //connect要放在这里 不然会nullptr exception
       connect(p1,&QProcess::readyReadStandardOutput,this,&mm_page::on_p1_ReadStdOutput);
       p1->start(strategyPath.absolutePath(), arguments);
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

void mm_page::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    p1_strategy = arg1;
}
