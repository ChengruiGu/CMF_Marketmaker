#ifndef SETTING_CHOOSEPRODUCT_H
#define SETTING_CHOOSEPRODUCT_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class setting_chooseProduct;
}

class setting_chooseProduct : public QDialog
{
    Q_OBJECT

public:
    explicit setting_chooseProduct(QWidget *parent = nullptr);
    ~setting_chooseProduct();

private slots:
    void on_pushButton_released();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_released();

private:
    Ui::setting_chooseProduct *ui;
    QSqlRelationalTableModel *model;
    int row_to_delete = -1;
};

#endif // SETTING_CHOOSEPRODUCT_H
