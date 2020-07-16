#ifndef SETTING_SETROLE_H
#define SETTING_SETROLE_H

#include <QDialog>

namespace Ui {
class setting_setrole;
}

class setting_setrole : public QDialog
{
    Q_OBJECT

public:
    explicit setting_setrole(QWidget *parent = nullptr);
    ~setting_setrole();

private:
    Ui::setting_setrole *ui;
};

#endif // SETTING_SETROLE_H
