#ifndef MM_PAGE_H
#define MM_PAGE_H

#include <QWidget>
#include <QProcess>

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

private slots:
    void on_pushButton_3_released();
    void on_p1_started();
    void on_p1_ReadStdOutput();

    void on_pushButton_4_released();

private:
    Ui::mm_page *ui;
    QProcess *p1;
    int p1_state = 0;
};

#endif // MM_PAGE_H
