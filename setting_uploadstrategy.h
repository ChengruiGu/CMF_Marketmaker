#ifndef SETTING_UPLOADSTRATEGY_H
#define SETTING_UPLOADSTRATEGY_H

#include <QDialog>

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

private:
    Ui::setting_uploadstrategy *ui;
};

#endif // SETTING_UPLOADSTRATEGY_H
