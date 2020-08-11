#include "db_controller.h"
#include <QMessageBox>
//参考 https://www.cnblogs.com/xia-weiwen/archive/2017/05/04/6806709.html

QSqlDatabase createDB(){
    QSqlDatabase database;

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MarketMakerDB");
    //setDatabaseName()的参数是数据库文件名。如果这个数据库不存在，则会在后续操作时自动创建
    //如果已经存在，则后续的操作会在已有的数据库上进行。

    return database;
}

bool createAllTables(QSqlDatabase db){

    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database",
                              "Unable to establish a database connection.\n"
                              "This example needs SQLite support. Please read "
                              "the Qt SQL driver documentation for information how "
                              "to build it.", QMessageBox::Cancel);
        return false;
    }

    QSqlQuery sql_query;
    //sql_query.exec("drop table users");
    QString create_sql =
            "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, name TEXT, role TEXT, phone TEXT, email TEXT, date TEXT, password TEXT)";
    sql_query.exec(create_sql);
    if(!sql_query.isActive()) return false;

    sql_query.exec("INSERT INTO users VALUES('cg487', '顾成睿', 'IT', '13570808796', 'cg487@cornell.edu', '2020-08-11', '0000')");

    //db.close();

    return true;
}

