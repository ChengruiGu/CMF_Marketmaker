#ifndef SETTING_MANAGEUSER_H
#define SETTING_MANAGEUSER_H

#include <QWidget>

namespace Ui {
class setting_manageuser;
}

class setting_manageuser : public QWidget
{
    Q_OBJECT

public:
    explicit setting_manageuser(QWidget *parent = nullptr);
    ~setting_manageuser();

private slots:
    void on_pushButton_2_released();

    void on_pushButton_released();

private:
    Ui::setting_manageuser *ui;
};

#endif // SETTING_MANAGEUSER_H
