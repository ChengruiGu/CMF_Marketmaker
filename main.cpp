#include "mainwindow.h"
#include "login_dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login_Dialog l;
    l.show();
    w.hide();
    if(l.exec() == QDialog::Accepted)
        w.show();
    return a.exec();
}
