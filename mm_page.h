#ifndef MM_PAGE_H
#define MM_PAGE_H

#include <QWidget>
#include <QProcess>

#include "mm_tradecontrol.h"

namespace Ui {
class mm_page;
}

class mm_page : public QWidget
{
    Q_OBJECT

public:
    explicit mm_page(QWidget *parent = nullptr);
    ~mm_page();
    void setName(QString s);
    void setName1(QString s);
    void refreshStrategyList();

private slots:
//    void on_pushButton_3_released();
//    void on_p1_started();
//    void on_p1_ReadStdOutput();

//    void on_pushButton_4_released();

//    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_mm_page_destroyed();

private:
    Ui::mm_page *ui;
//    QProcess *p1;
//    int p1_state = 0;
//    QString p1_strategy;

    mm_tradecontrol *tc1;
    mm_tradecontrol *tc2;
    mm_tradecontrol *tc3;
    mm_tradecontrol *tc4;
    mm_tradecontrol *tc5;
};

#endif // MM_PAGE_H
