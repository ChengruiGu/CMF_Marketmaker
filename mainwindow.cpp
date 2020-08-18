#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mm_page.h"
#include "mm_page2.h"
#include "future_mm.h"
#include "setting_createrole.h"
#include "setting_resetpwd.h"
#include "setting_chooseproduct.h"
#include "setting_setmm.h"
#include "setting_changepwd.h"
#include "setting_riskprmt.h"
#include "setting_manageuser.h"
#include "setting_setrole.h"
#include "setting_addconract.h"
#include "setting_uploadstrategy.h"
#include "twolabel.h"
#include "account_login.h"
#include "welcome_page.h"
#include "setting_riskctrlfold.h"
#include "db_controller.h"

#include <QtWidgets>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("招证资本投资有限公司做市系统");

    pagesWidget = new QTabWidget;
    pagesWidget->setTabsClosable(true);
    future_page = new mm_page;
    setCentralWidget(pagesWidget);
    this->showMaximized();

    //欢迎页 不兼容mm_page暂时不能用
//    welcome_page *wp = new welcome_page;
//    pagesWidget->addTab(wp,0);
//    pagesWidget->setCurrentIndex(0);

    //数据库初始化
    QSqlDatabase db = createDB();
    createAllTables(db);


    // 底部状态栏 显示账户信息
    QPushButton *acnt_login = new QPushButton;
    acnt_login->setText("登录交易账户");

    twoLabel *tl5 = new twoLabel;
    tl5->setLabel1("账户状态：");
    tl5->setLabel2("已登录");

    twoLabel *tl1 = new twoLabel;
    tl1->setLabel1("静态权益：");
    tl1->setLabel2("50426875.53");

    twoLabel *tl2 = new twoLabel;
    tl2->setLabel1("平仓盈亏：");
    tl2->setLabel2("0.00");

    twoLabel *tl3 = new twoLabel;
    tl3->setLabel1("持仓盈亏：");
    tl3->setLabel2("-58.00");

    twoLabel *tl4 = new twoLabel;
    tl4->setLabel1("手续费：");
    tl4->setLabel2("134.00");

    twoLabel *tl6 = new twoLabel;
    tl6->setLabel1("保证金占用:");
    tl6->setLabel2("345.00");

    statusBar()->addPermanentWidget(acnt_login);
    statusBar()->addPermanentWidget(tl5);
    statusBar()->addPermanentWidget(tl1);
    statusBar()->addPermanentWidget(tl2);
    statusBar()->addPermanentWidget(tl3);
    statusBar()->addPermanentWidget(tl4);
    statusBar()->addPermanentWidget(tl6);

    //状态栏关联登录交易账户
    connect(acnt_login, &QPushButton::released, this, &MainWindow::login_tradeAcnt);

    //tab栏关闭tab
    connect(pagesWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeMyTab);

    //设置策略文件夹
    QDir targetDir("./strategies");
    if(!targetDir.exists()){    // 如果目标目录不存在，则进行创建
        if(!targetDir.mkdir(targetDir.absolutePath())){
            qWarning("Cannot create strategies folder!!!");
            return;
        }
    }

    //顶部菜单栏连接
    //上期所
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
    connect(this->ui->actionyuanyou,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiondiliu,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionliqing,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiontianjiao,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->action20hao,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionzhijiang,&QAction::triggered,this,&MainWindow::setFuturePage);

    //郑商所
    connect(this->ui->actionbaitang,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionmianhua,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionpumai,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionqiangmai,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionzaoxiandao,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionwanxiandao,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjindao,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actioncaizipo,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionyoucaizi,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actioncaiziyou,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionpiguo,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionmiansha,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionhongzao,&QAction::triggered,this,&MainWindow::setFuturePage);

    //大商所
    //TODO:顶部菜单栏连接所有商品


    // 期权页关联
    connect(this->ui->actiontong_op,&QAction::triggered,this,&MainWindow::setOptionPage);

    //设置菜单
    connect(this->ui->actioncjyh,&QAction::triggered,this,&MainWindow::createRole);
    connect(this->ui->actionpzsz,&QAction::triggered,this,&MainWindow::chooseProduct);
    connect(this->ui->actionzssz,&QAction::triggered,this,&MainWindow::setMm);
    connect(this->ui->actiondhyfk,&QAction::triggered,this,&MainWindow::riskControl);
    connect(this->ui->actionmmxg,&QAction::triggered,this,&MainWindow::changePwd);
    connect(this->ui->actionjkzb,&QAction::triggered,this,&MainWindow::riskParameter);
    connect(this->ui->actionjsgl,&QAction::triggered,this,&MainWindow::setRole);
    connect(this->ui->actiontjhy,&QAction::triggered,this,&MainWindow::setContract);
    connect(this->ui->actionsccl,&QAction::triggered,this,&MainWindow::addStrategy);
    connect(this->ui->actionfksz,&QAction::triggered,this,&MainWindow::riskControl);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFuturePage(){
    mm_page *np = new mm_page;
    QAction *a = qobject_cast<QAction*>(sender());
    QString s = a->text();
    int idx = pagesWidget->addTab(np,s); //mm_page
    np->setName(s);
    pagesWidget->setCurrentIndex(idx);
}

void MainWindow::setOptionPage(){
    QAction *a = qobject_cast<QAction*>(sender());
    QString s = a->text();
    future_page->setName1(s);
}

void MainWindow::closeMyTab(int i){
    pagesWidget->removeTab(i);
}

//资源占用参考https://blog.csdn.net/qq_27905767/article/details/88635420
//TODO:解决资源占用问题 暂时对性能影响较小
void MainWindow::login_tradeAcnt(){
    account_login *al = new account_login;
    al->show();
}

void MainWindow::createRole(){
    setting_manageuser *mu = new setting_manageuser;
    mu->show();
}


void MainWindow::chooseProduct(){
    setting_chooseProduct *cp = new setting_chooseProduct;
    cp->exec();
}

void MainWindow::setMm(){
    setting_setmm *sm = new setting_setmm;
    sm->exec();
}

void MainWindow::riskControl(){
    setting_riskctrlfold *rc = new setting_riskctrlfold;
    rc->show();
}

void MainWindow::changePwd(){
    setting_changepwd *cp = new setting_changepwd;
    cp->exec();
}

void MainWindow::riskParameter(){
    setting_riskprmt *rp = new setting_riskprmt;
    rp->exec();
}

void MainWindow::setRole(){
    setting_setrole *sr = new setting_setrole;
    sr->exec();
}

void MainWindow::setContract(){
    setting_addconract *ac = new setting_addconract;
    ac->exec();
}

void MainWindow::addStrategy(){
    setting_uploadstrategy *us = new setting_uploadstrategy;
    us->exec(); //exec() 会block, 除非关闭当前小窗口否则无法操作大窗口
    for(int i = 0; i < pagesWidget->count(); ++i){
        mm_page *mp = qobject_cast<mm_page*>(pagesWidget->widget(i)); //类型转换
        mp->refreshStrategyList();
    }
}
