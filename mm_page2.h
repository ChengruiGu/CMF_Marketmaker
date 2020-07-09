#ifndef MM_PAGE2_H
#define MM_PAGE2_H

#include <QWidget>

namespace Ui {
class mm_page2;
}

class mm_page2 : public QWidget
{
    Q_OBJECT

public:
    explicit mm_page2(QWidget *parent = nullptr);
    ~mm_page2();

private:
    Ui::mm_page2 *ui;
};

#endif // MM_PAGE2_H
