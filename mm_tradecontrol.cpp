#include "mm_tradecontrol.h"
#include "ui_mm_tradecontrol.h"

/*
 * 策略交易控件，在mm_page中加载
 * QPlainTextEdit *output: 策略运行时输出到的控件
 * QStringList s_List：可运行的策略列表
 */
mm_tradecontrol::mm_tradecontrol(QString contract_code, QPlainTextEdit *output, QStringList s_List, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mm_tradecontrol)
{
    ui->setupUi(this);
    ui->label_2->setText(contract_code);
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
    if(proc_strategy.isEmpty()) return;

    //创建进程
    QString program = "./strategies/";
    program.append(proc_strategy);
    QDir strategyPath(program);

    //启动参数
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

//读取输出 每当进程输出到stdoutput上就会调用这个函数
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
    for(int i = 0; i < strategyList.length(); ++i){
        ui->comboBox->addItem(strategyList[i]);
    }
}

//给上层mm_page保留的public方法 用来全部启动
void mm_tradecontrol::start_trading(){
    on_pushButton_2_released();
}

//给上层mm_page保留的public方法 用来全部暂停
void mm_tradecontrol::suspend_trading(){
    on_pushButton_3_released();
}
