#ifndef SETTING_RISKCTRL_H
#define SETTING_RISKCTRL_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class setting_riskctrl;
}

class setting_riskctrl : public QDialog
{
    Q_OBJECT

public:
    explicit setting_riskctrl(QWidget *parent = nullptr);
    ~setting_riskctrl();

private slots:
    void setContract(QModelIndex qi);

private:
    Ui::setting_riskctrl *ui;
    QStandardItemModel* model;
};

#endif // SETTING_RISKCTRL_H
