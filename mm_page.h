#ifndef MM_PAGE_H
#define MM_PAGE_H

#include <QWidget>

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

private:
    Ui::mm_page *ui;
};

#endif // MM_PAGE_H
