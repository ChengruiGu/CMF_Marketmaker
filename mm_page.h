#ifndef MM_PAGE_H
#define MM_PAGE_H

#include <QWidget>
#include <QProcess>
#include <QtSql>

#include "mm_tradecontrol.h"

namespace Ui {
class mm_page;
}

class mm_page : public QWidget
{
    Q_OBJECT

public:
    explicit mm_page(QString username, QString future_name, QWidget *parent = nullptr);
    ~mm_page();
    void setName(QString s);
    void setName1(QString s);

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_mm_page_destroyed();

private:
    Ui::mm_page *ui;
    QString username;
    QVector<QString> contracts; //所有可交易合约
    QVector<mm_tradecontrol *> trade_controls; //所有mm_tradecontrol

};

#endif // MM_PAGE_H
