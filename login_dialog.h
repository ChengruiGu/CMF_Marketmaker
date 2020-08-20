#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Login_Dialog;
}

class Login_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Dialog(QWidget *parent = nullptr);
    ~Login_Dialog();

private slots:
    void on_pushButton_released();

private:
    Ui::Login_Dialog *ui;
};

#endif // LOGIN_DIALOG_H
