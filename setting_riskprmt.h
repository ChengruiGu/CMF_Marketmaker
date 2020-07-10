#ifndef SETTING_RISKPRMT_H
#define SETTING_RISKPRMT_H

#include <QDialog>

namespace Ui {
class setting_riskprmt;
}

class setting_riskprmt : public QDialog
{
    Q_OBJECT

public:
    explicit setting_riskprmt(QWidget *parent = nullptr);
    ~setting_riskprmt();

private:
    Ui::setting_riskprmt *ui;
};

#endif // SETTING_RISKPRMT_H
