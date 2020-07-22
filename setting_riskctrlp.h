#ifndef SETTING_RISKCTRLP_H
#define SETTING_RISKCTRLP_H

#include <QDialog>

namespace Ui {
class setting_riskctrlp;
}

class setting_riskctrlp : public QDialog
{
    Q_OBJECT

public:
    explicit setting_riskctrlp(QWidget *parent = nullptr);
    ~setting_riskctrlp();

private:
    Ui::setting_riskctrlp *ui;
};

#endif // SETTING_RISKCTRLP_H
