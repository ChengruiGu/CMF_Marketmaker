#ifndef SETTING_SETMM_H
#define SETTING_SETMM_H

#include <QDialog>

namespace Ui {
class setting_setmm;
}

class setting_setmm : public QDialog
{
    Q_OBJECT

public:
    explicit setting_setmm(QWidget *parent = nullptr);
    ~setting_setmm();

private:
    Ui::setting_setmm *ui;
};

#endif // SETTING_SETMM_H
