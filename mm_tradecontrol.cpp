#include "mm_tradecontrol.h"
#include "ui_mm_tradecontrol.h"

mm_tradecontrol::mm_tradecontrol(QPlainTextEdit *output, QStringList s_List,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_tradecontrol)
{
    ui->setupUi(this);
    this->outside_display = output;
    this->strategyList = s_List;
    refreshStrategyList();
}

mm_tradecontrol::~mm_tradecontrol()
{
    delete ui;
}

//选中策略
void mm_tradecontrol::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(!proc_state){ //仅在没有进程运行时才调整策略
        proc_strategy = arg1;
        ui->label_5->setText(proc_strategy);
    }
}

//启动按钮
void mm_tradecontrol::on_pushButton_2_released()
{
    if(proc_state) return; //只允许一个进程处于运行中

    //创建进程
       QString program = "./strategies/";
       program.append(proc_strategy);
       QDir strategyPath(program);

       QStringList arguments;

       proc = new QProcess(this);
       //connect要放在这里 不然会nullptr exception
       connect(proc,&QProcess::readyReadStandardOutput,this,&mm_tradecontrol::on_proc_ReadStdOutput);
       proc->start(strategyPath.absolutePath(), arguments);
       proc_state = 1;

       //运行状态标签
       ui->label_3->setText("运行中");
       ui->label_3->setStyleSheet("QLabel {color : red; }");
}

//读取输出
void mm_tradecontrol::on_proc_ReadStdOutput(){
    char buf[1024];
    qint64 lineLength = proc->readLine(buf, sizeof(buf));
        if (lineLength != -1) {
            QString s = QString::fromLocal8Bit(buf);
            this->outside_display->appendPlainText(s); // thread safety???
        }
}

//停止按钮
void mm_tradecontrol::on_pushButton_3_released()
{
    if(!proc_state) return;
    proc->kill();
    proc_state = 0;

    ui->label_3->setText("已暂停");
    ui->label_3->setStyleSheet("QLabel {color : blue; }");
}

//刷新策略列表
void mm_tradecontrol::refreshStrategyList(){
    ui->comboBox->clear();
    for(int i = 2; i < strategyList.length(); ++i){
        QDir strategyName(strategyList[i]);
        ui->comboBox->addItem(strategyName.dirName());
    }
}

void mm_tradecontrol::start_trading(){
    on_pushButton_2_released();
}

void mm_tradecontrol::suspend_trading(){
    on_pushButton_3_released();
}
