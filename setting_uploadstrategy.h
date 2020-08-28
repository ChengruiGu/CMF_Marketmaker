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

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_7_released();

    void on_pushButton_8_released();

private:
void clear_checkboxes();
void clear_checkboxes_2();

private:
    Ui::setting_uploadstrategy *ui;
    QMap<QString, QCheckBox*> contracts; //合约与对应checkbox
    QSqlTableModel *model; //策略显示模型
    QMap<QString, QCheckBox*> strategies; //策略与对应checkbox
    QSqlTableModel *model_2; //参数显示模型
};

#endif // SETTING_UPLOADSTRATEGY_H
