#ifndef SETTING_CHANGEPWD_H
#define SETTING_CHANGEPWD_H

#include <QDialog>

namespace Ui {
class setting_changepwd;
}

class setting_changepwd : public QDialog
{
    Q_OBJECT

public:
    explicit setting_changepwd(QWidget *parent = nullptr);
    ~setting_changepwd();

private:
    Ui::setting_changepwd *ui;
};

#endif // SETTING_CHANGEPWD_H
