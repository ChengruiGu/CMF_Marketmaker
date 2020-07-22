#ifndef TWOLABEL_H
#define TWOLABEL_H

#include <QWidget>

namespace Ui {
class twoLabel;
}

class twoLabel : public QWidget
{
    Q_OBJECT

public:
    explicit twoLabel(QWidget *parent = nullptr);
    ~twoLabel();

    void setLabel1(QString s);
    void setLabel2(QString s);

private:
    Ui::twoLabel *ui;
};

#endif // TWOLABEL_H
