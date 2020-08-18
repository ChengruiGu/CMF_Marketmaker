#ifndef SETTING_ADDCONRACT_H
#define SETTING_ADDCONRACT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class setting_addconract;
}

class setting_addconract : public QDialog
{
    Q_OBJECT

public:
    explicit setting_addconract(QWidget *parent = nullptr);
    ~setting_addconract();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::setting_addconract *ui;
    QSqlRelationalTableModel *model;
    int row_to_delete = -1;
};

#endif // SETTING_ADDCONRACT_H
