#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mm_page.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setFuturePage();
    void setOptionPage();
    void createRole();
    void chooseProduct();
    void setMm();
    void riskControl();
    void changePwd();
    void riskParameter();
    void setRole();
    void setContract();
    void closeMyTab(int i);
    void login_tradeAcnt();
    void addStrategy();
    void riskParameterP();
    void riskControlProduct();
    void riskControlCategory();

private:
    Ui::MainWindow *ui;
    QTabWidget *pagesWidget;
    mm_page *future_page;

};
#endif // MAINWINDOW_H
