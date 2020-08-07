#ifndef MM_TRADECONTROL_H
#define MM_TRADECONTROL_H

#include <QWidget>
#include <QProcess>
#include <QDir>
#include <QPlainTextEdit>

namespace Ui {
class mm_tradecontrol;
}

class mm_tradecontrol : public QWidget
{
    Q_OBJECT

public:
    explicit mm_tradecontrol(QPlainTextEdit *output, QStringList s_List, QWidget *parent = nullptr);
    ~mm_tradecontrol();
    void refreshStrategyList();
    void start_trading(); //由全部启动按钮调用，默认tradecontrol已初始化
    void suspend_trading(); //由全部启动按钮调用，默认tradecontrol已初始化

public:
    QStringList strategyList;

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_proc_ReadStdOutput();


private:
    Ui::mm_tradecontrol *ui;
    QProcess *proc;
    int proc_state = 0;
    QString proc_strategy;

    QPlainTextEdit *outside_display;
};

#endif // MM_TRADECONTROL_H
