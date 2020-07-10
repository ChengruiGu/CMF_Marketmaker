#ifndef SETTING_CHOOSEPRODUCT_H
#define SETTING_CHOOSEPRODUCT_H

#include <QDialog>

namespace Ui {
class setting_chooseProduct;
}

class setting_chooseProduct : public QDialog
{
    Q_OBJECT

public:
    explicit setting_chooseProduct(QWidget *parent = nullptr);
    ~setting_chooseProduct();

private:
    Ui::setting_chooseProduct *ui;
};

#endif // SETTING_CHOOSEPRODUCT_H
