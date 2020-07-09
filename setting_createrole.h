#ifndef SETTING_CREATEROLE_H
#define SETTING_CREATEROLE_H

#include <QDialog>

namespace Ui {
class setting_createRole;
}

class setting_createRole : public QDialog
{
    Q_OBJECT

public:
    explicit setting_createRole(QDialog *parent = nullptr);
    ~setting_createRole();

private slots:
    void on_pushButton_released();

private:
    Ui::setting_createRole *ui;
};

#endif // SETTING_CREATEROLE_H
