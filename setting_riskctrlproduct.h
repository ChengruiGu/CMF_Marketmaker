#ifndef SETTING_RISKCTRLPRODUCT_H
#define SETTING_RISKCTRLPRODUCT_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class setting_riskctrlproduct;
}

class setting_riskctrlproduct : public QDialog
{
    Q_OBJECT

public:
    explicit setting_riskctrlproduct(QWidget *parent = nullptr);
    ~setting_riskctrlproduct();

private slots:
    void setProduct(QModelIndex qi);

private:
    Ui::setting_riskctrlproduct *ui;
    QStandardItemModel *model;
};

#endif // SETTING_RISKCTRLPRODUCT_H
