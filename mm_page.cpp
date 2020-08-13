#include "mm_page.h"
#include "ui_mm_page.h"
#include "bar.h"
#include "mm_tradecontrol.h"
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

    QDir strategyDir(QString("./strategies"));
    QStringList strategyList = strategyDir.entryList();

    //后续可以用一个vector管理所有tradecontrol，这里暂时先写死
    tc1 = new mm_tradecontrol(ui->plainTextEdit, strategyList);
    tc2 = new mm_tradecontrol(ui->plainTextEdit, strategyList);
    tc3 = new mm_tradecontrol(ui->plainTextEdit, strategyList);
    ui->verticalLayout_7->addWidget(tc1);
    ui->verticalLayout_7->addWidget(tc2);
    ui->verticalLayout_7->addWidget(tc3);

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
    QDir strategyDir(QString("./strategies"));
    QStringList strategyList = strategyDir.entryList();
    tc1->strategyList = strategyList;
    tc1->refreshStrategyList();

    tc2->strategyList = strategyList;
    tc2->refreshStrategyList();

    tc3->strategyList = strategyList;
    tc3->refreshStrategyList();
}

//全部启动
void mm_page::on_pushButton_released()
{
    tc1->start_trading();
    tc2->start_trading();
    tc3->start_trading();
}

//全部停止
void mm_page::on_pushButton_2_released()
{
    tc1->suspend_trading();
    tc2->suspend_trading();
    tc3->suspend_trading();
}

void mm_page::on_mm_page_destroyed()
{
    on_pushButton_2_released();
}
