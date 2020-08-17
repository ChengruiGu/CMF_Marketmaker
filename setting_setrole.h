#ifndef SETTING_SETROLE_H
#define SETTING_SETROLE_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QStandardItemModel>

namespace Ui {
class setting_setrole;
}

class setting_setrole : public QDialog
{
    Q_OBJECT

public:
    explicit setting_setrole(QWidget *parent = nullptr);
    ~setting_setrole();

private slots:
    void on_listView_clicked(const QModelIndex &index);
    void on_pushButton_released();

private:
    void clear_checkboxes();

private:
    Ui::setting_setrole *ui;
    QStandardItemModel *model;
    int current;
    QMap<QString, QCheckBox*> checkboxes;
    QVector<QString> role_vec;
};

#endif // SETTING_SETROLE_H
