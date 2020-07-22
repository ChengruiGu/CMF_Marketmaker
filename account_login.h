#ifndef ACCOUNT_LOGIN_H
#define ACCOUNT_LOGIN_H

#include <QDialog>

namespace Ui {
class account_login;
}

class account_login : public QDialog
{
    Q_OBJECT

public:
    explicit account_login(QWidget *parent = nullptr);
    ~account_login();

private:
    Ui::account_login *ui;
};

#endif // ACCOUNT_LOGIN_H
