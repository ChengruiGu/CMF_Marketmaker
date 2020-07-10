#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void resetPwd();
    void chooseProduct();
    void setMm();
    void riskControl();
    void changePwd();
    void riskParameter();

private:
    Ui::MainWindow *ui;
    QStackedWidget *pagesWidget;

};
#endif // MAINWINDOW_H
