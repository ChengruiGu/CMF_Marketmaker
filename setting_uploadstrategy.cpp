#include "setting_uploadstrategy.h"
#include "ui_setting_uploadstrategy.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

setting_uploadstrategy::setting_uploadstrategy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_uploadstrategy)
{
    ui->setupUi(this);
}

setting_uploadstrategy::~setting_uploadstrategy()
{
    delete ui;
}

void setting_uploadstrategy::on_pushButton_released()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题","/","(*.exe)"); //QFileDialog是windows的上传文件界面，用法参考doc
    ui->label_2->setText(file_name);
}

/* 复制上传的策略到/strategies文件夹内
 * 该方法参考http://qiusuoge.com/12051.html*/
void setting_uploadstrategy::on_pushButton_2_released()
{
    QString src_path = ui->label_2->text();
    if(src_path == "Not Selected"){
        QMessageBox msgBox;
        msgBox.setText("请先选择要上传的策略！");
        msgBox.exec();
        return;
    }

    QString strategy_name = ui->lineEdit->text(); //获取策略名称
    strategy_name.replace(QString(" "),QString("")); //替换所有空格
    if(strategy_name == ""){
        QMessageBox msgBox;
        msgBox.setText("策略名不能为空！");
        msgBox.exec();
        return;
    }

    src_path.replace("\\","/"); //调整路径格式
    QString dest("./strategies/");
    dest.append(strategy_name);
    dest.append(".exe");

    QDir *createfile = new QDir;
    bool exist = createfile->exists(dest);
    if (exist){
        QMessageBox msgBox;
        msgBox.setText("同名策略已存在，是否替换？");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            createfile->remove(dest);
        } else {
            return;
        }
    }

    if(!QFile::copy(src_path, dest))
    {
        qWarning("copy strategy failed!!!");
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("上传成功");
    msgBox.exec();

}
