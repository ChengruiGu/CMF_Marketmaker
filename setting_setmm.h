#ifndef SETTING_SETMM_H
#define SETTING_SETMM_H

#include <QDialog>
#include <QtSql>
#include <QCheckBox>
#include <QStandardItemModel>

namespace Ui {
class setting_setmm;
}

class setting_setmm : public QDialog
{
    Q_OBJECT

public:
    explicit setting_setmm(QWidget *parent = nullptr);
    ~setting_setmm();

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_released();

private:
    void clear_checkboxes();

private:
    Ui::setting_setmm *ui;
    QMap<QString, QCheckBox*> contracts;
    QStandardItemModel *model;
};

#endif // SETTING_SETMM_H
