#ifndef SETTING_RESETPWD_H
#define SETTING_RESETPWD_H

#include <QDialog>

namespace Ui {
class setting_resetPwd;
}

class setting_resetPwd : public QDialog
{
    Q_OBJECT

public:
    explicit setting_resetPwd(QWidget *parent = nullptr);
    ~setting_resetPwd();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::setting_resetPwd *ui;
};

#endif // SETTING_RESETPWD_H
