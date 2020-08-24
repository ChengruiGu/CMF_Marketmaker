#include "setting_setrole.h"
#include "ui_setting_setrole.h"

#include <QMessageBox>

setting_setrole::setting_setrole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting_setrole)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);

    /*管理员应该默认且永久拥有所有权限*/

    model->setColumnCount(1);
    model->setItem(0, 0, new QStandardItem("管理员"));
    model->setItem(1, 0, new QStandardItem("交易员"));
    model->setItem(2, 0, new QStandardItem("风控员"));
    model->setItem(3, 0, new QStandardItem("IT"));

    role_vec.push_back("管理员");
    role_vec.push_back("交易员");
    role_vec.push_back("风控员");
    role_vec.push_back("IT");

    ui->listView->setModel(model);
    ui->listView->setCurrentIndex(model->index(0,0)); //默认选中角色第一项

    current = 0;

    //设置checkboxes map
    checkboxes["用户管理"] = ui->checkBox;
    checkboxes["角色管理"] = ui->checkBox_2;
    checkboxes["品种设置"] = ui->checkBox_3;
    checkboxes["做市权限设置"] = ui->checkBox_4;
    checkboxes["风控设置"] = ui->checkBox_5;
    checkboxes["监控指标"] = ui->checkBox_6;
    checkboxes["合约管理"] = ui->checkBox_7;
    checkboxes["策略管理"] = ui->checkBox_8;

    on_listView_clicked(model->index(0,0)); //默认显示角色第一项权限
}

setting_setrole::~setting_setrole()
{
    delete ui;
}

//checkBox     用户管理
//checkBox_2   角色管理
//checkBox_3   品种设置
//checkBox_4   做市权限设置
//checkBox_5   风控设置
//checkBox_6   监控指标
//checkBox_7   合约管理
//checkBox_8   策略管理

void setting_setrole::on_listView_clicked(const QModelIndex &index)
{
    current = index.row(); //最新的点击对象序号
    QString role_name = role_vec[current]; //点击对象的角色名

    clear_checkboxes(); //清空checkboxes

    QSqlQuery query; //查找对应权限
    query.prepare("SELECT function_name FROM privileges WHERE role_name = :role_name;");
    query.bindValue(":role_name", role_name);
    if(!query.exec()) qDebug() << query.lastError();

    while(query.next()){ //更新checkboxes
        QString function = query.value(0).toString();
        checkboxes[function]->setChecked(true);
    }

}

/*删除或添加权限*/
void setting_setrole::on_pushButton_released()
{
    QString role_name = role_vec[current];

    if(role_name == "管理员"){
        QMessageBox msgBox;
        msgBox.setText("管理员默认拥有所有权限，无法修改");
        msgBox.exec();
        on_listView_clicked(model->index(0,0));
        return;
    }

    QSqlQuery query;
    QMap<QString, QCheckBox*>::const_iterator i = checkboxes.constBegin();
    while (i != checkboxes.constEnd()) {
        if(i.value()->isChecked()){ //如果被打钩则添加权限
            query.prepare("INSERT INTO privileges VALUES(:role_name, :function_name)");
            query.bindValue(":role_name", role_name);
            query.bindValue(":function_name", i.value()->text());
            query.exec();
        } else { //如果没被打钩则删除权限
            query.prepare("DELETE FROM privileges WHERE role_name = :role_name AND function_name = :function_name");
            query.bindValue(":role_name", role_name);
            query.bindValue(":function_name", i.value()->text());
            query.exec();
        }
        ++i;
    }
}

void setting_setrole::clear_checkboxes(){
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
}
