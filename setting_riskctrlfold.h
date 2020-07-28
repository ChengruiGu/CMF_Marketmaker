#ifndef SETTING_RISKCTRLFOLD_H
#define SETTING_RISKCTRLFOLD_H

#include <QWidget>
#include "setting_riskctrl.h"
#include "setting_riskctrlcategory.h"
#include "setting_riskctrlp.h"
#include "setting_riskctrlproduct.h"

namespace Ui {
class setting_riskctrlfold;
}

class setting_riskctrlfold : public QWidget
{
    Q_OBJECT

public:
    explicit setting_riskctrlfold(QWidget *parent = nullptr);
    ~setting_riskctrlfold();

private slots:
    void setdhy();
    void setpz();
    void setpl();
void setzh();

private:
    Ui::setting_riskctrlfold *ui;
    int v1, v2, v3, v4;
    setting_riskctrl *dhy;
    setting_riskctrlproduct *pz;
    setting_riskctrlcategory *pl;
    setting_riskctrlp *zh;
};

#endif // SETTING_RISKCTRLFOLD_H
