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
    this->setWindowTitle("XX资本投资有限公司做市系统");

    default_widget = new QWidget;
    /* 这里用到了css 教程参考https://www.runoob.com/css/css-tutorial.html
       一般直接搜索css + 想要的效果, 比如 css set background image 就能查到怎么设置背景图片*/
    default_widget->setStyleSheet("background-image: url(:/e_tea.jpg);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center;"
                                  "background-color:rgb(255,255,255)");

    setCentralWidget(default_widget);

    pagesWidget = new QTabWidget;
    pagesWidget->setTabsClosable(true);



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

    //设置参数文件夹
    QDir prmtDir("./parameters");
    if(!prmtDir.exists()){    // 如果目标目录不存在，则进行创建
        if(!prmtDir.mkdir(prmtDir.absolutePath())){
            qWarning("Cannot create parameters folder!!!");
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
    connect(this->ui->actionliqing,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiontianjiao,&QAction::triggered,this,&MainWindow::setFuturePage);
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

    connect(this->ui->actiondonglimei,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionPTA,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjiachun,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionboli,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionguitie,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionguimeng,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionniaosu,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionchunjian,&QAction::triggered,this,&MainWindow::setFuturePage);

    //大商所
    connect(this->ui->actionyumi,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionyumidianfen,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionhuangdaou1,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionhuangdadou2,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiondoupo,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiondouyou,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionzonglvyou,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionxianweiban,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjiaoheban,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjidan,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjingmi,&QAction::triggered,this,&MainWindow::setFuturePage);

    connect(this->ui->actionjyx,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjlyx,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjbx,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjt,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionjm,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiontks,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionyec,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionbyx,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionyhsyq,&QAction::triggered,this,&MainWindow::setFuturePage);

    //中金所
    connect(this->ui->actionif,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionih,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionic,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiontf,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actiont,&QAction::triggered,this,&MainWindow::setFuturePage);
    connect(this->ui->actionts,&QAction::triggered,this,&MainWindow::setFuturePage);


    // TODO: 期权页关联
    //connect(this->ui->actiontong_op,&QAction::triggered,this,&MainWindow::setOptionPage);

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
    connect(this->pagesWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::on_tab_close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* 添加期货页 */
void MainWindow::setFuturePage(){
    if(pagesWidget->count()==0){ //保存先前页面，防止setCentralWidget把它删了
        this->centralWidget()->setParent(0);
        setCentralWidget(pagesWidget);
    }
    QAction *a = qobject_cast<QAction*>(sender());
    QString s = a->text();
    mm_page *np = new mm_page("cg487", s);
    int idx = pagesWidget->addTab(np,s); //mm_page
    pagesWidget->setCurrentIndex(idx);
}

/* 添加期权页(TODO) */
void MainWindow::setOptionPage(){
    //    QAction *a = qobject_cast<QAction*>(sender());
    //    QString s = a->text();
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

/* 交易页面和系统功能被设计成互斥的：假如有交易页面被打开，那么用户管理、策略管理等功能都不可用。
 * 不这样做会带来很多问题，比如假如正在交易中的合约被删除该怎么办、正在交易中的品种被删除该怎么办
 * 等等。互斥保证了交易系统的功能之间不会互相干扰。
*/

/* 用户管理 */
void MainWindow::createRole(){
    if(pagesWidget->count()){
        QMessageBox msgBox;
        msgBox.setText("请先关闭所有交易页面！");
        msgBox.exec();
        return;
    }
    setting_manageuser *mu = new setting_manageuser;
    mu->show();
}

/* 品种管理 */
void MainWindow::chooseProduct(){
    if(pagesWidget->count()){
        QMessageBox msgBox;
        msgBox.setText("请先关闭所有交易页面！");
        msgBox.exec();
        return;
    }
    setting_chooseProduct *cp = new setting_chooseProduct;
    cp->exec();
}

/* 做市权限管理 */
void MainWindow::setMm(){
    if(pagesWidget->count()){
        QMessageBox msgBox;
        msgBox.setText("请先关闭所有交易页面！");
        msgBox.exec();
        return;
    }
    setting_setmm *sm = new setting_setmm;
    sm->exec();
}

/* 风控管理 */
void MainWindow::riskControl(){
    setting_riskctrlfold *rc = new setting_riskctrlfold;
    rc->show();
}

/* 修改密码 */
void MainWindow::changePwd(){
    setting_changepwd *cp = new setting_changepwd;
    cp->exec();
}

/* 风控数据读取设置 */
void MainWindow::riskParameter(){
    setting_riskprmt *rp = new setting_riskprmt;
    rp->exec();
}

/* 角色管理 */
void MainWindow::setRole(){
    if(pagesWidget->count()){
        QMessageBox msgBox;
        msgBox.setText("请先关闭所有交易页面！");
        msgBox.exec();
        return;
    }
    setting_setrole *sr = new setting_setrole;
    sr->exec();
}

/* 合约管理 */
void MainWindow::setContract(){
    if(pagesWidget->count()){
        QMessageBox msgBox;
        msgBox.setText("请先关闭所有交易页面！");
        msgBox.exec();
        return;
    }
    setting_addconract *ac = new setting_addconract;
    ac->exec();
}

/* 策略、参数管理 */
void MainWindow::addStrategy(){
    if(pagesWidget->count()){
        QMessageBox msgBox;
        msgBox.setText("请先关闭所有交易页面！");
        msgBox.exec();
        return;
    }
    setting_uploadstrategy *us = new setting_uploadstrategy;
    us->exec(); //exec() 会block, 除非关闭当前小窗口否则无法操作大窗口
}

void MainWindow::on_tab_close(){
    if(this->pagesWidget->count() == 0){
        this->centralWidget()->setParent(0); //保存先前页面，防止setCentralWidget把它删了
        setCentralWidget(default_widget);
    }
}
