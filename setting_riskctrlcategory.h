#ifndef SETTING_RISKCTRLCATEGORY_H
#define SETTING_RISKCTRLCATEGORY_H

#include <QDialog>

namespace Ui {
class setting_riskctrlcategory;
}

class setting_riskctrlcategory : public QDialog
{
    Q_OBJECT

public:
    explicit setting_riskctrlcategory(QWidget *parent = nullptr);
    ~setting_riskctrlcategory();

private:
    Ui::setting_riskctrlcategory *ui;
};

#endif // SETTING_RISKCTRLCATEGORY_H
