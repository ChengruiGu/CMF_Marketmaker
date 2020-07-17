#ifndef SETTING_ADDCONRACT_H
#define SETTING_ADDCONRACT_H

#include <QDialog>

namespace Ui {
class setting_addconract;
}

class setting_addconract : public QDialog
{
    Q_OBJECT

public:
    explicit setting_addconract(QWidget *parent = nullptr);
    ~setting_addconract();

private:
    Ui::setting_addconract *ui;
};

#endif // SETTING_ADDCONRACT_H
