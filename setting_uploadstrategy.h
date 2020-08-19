#ifndef SETTING_UPLOADSTRATEGY_H
#define SETTING_UPLOADSTRATEGY_H

#include <QDialog>
#include <QCheckBox>
#include <QtSql>

namespace Ui {
class setting_uploadstrategy;
}

class setting_uploadstrategy : public QDialog
{
    Q_OBJECT

public:
    explicit setting_uploadstrategy(QWidget *parent = nullptr);
    ~setting_uploadstrategy();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_released();

    void on_pushButton_6_released();

private:
void clear_checkboxes();

private:
    Ui::setting_uploadstrategy *ui;
    QMap<QString, QCheckBox*> contracts;
    QSqlTableModel *model;
};

#endif // SETTING_UPLOADSTRATEGY_H
