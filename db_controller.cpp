#include "db_controller.h"
#include <QMessageBox>
//参考 https://www.cnblogs.com/xia-weiwen/archive/2017/05/04/6806709.html
#include <QtDebug>

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
    sql_query.exec("PRAGMA foreign_keys = ON");
    QString create_sql;

    /*****************功能表functions***************/
    create_sql =
            "CREATE TABLE IF NOT EXISTS functions ("
            "function_name TEXT PRIMARY KEY"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    sql_query.exec("INSERT INTO functions VALUES('用户管理')");
    sql_query.exec("INSERT INTO functions VALUES('角色管理')");
    sql_query.exec("INSERT INTO functions VALUES('品种设置')");
    sql_query.exec("INSERT INTO functions VALUES('做市权限设置')");
    sql_query.exec("INSERT INTO functions VALUES('风控设置')");
    sql_query.exec("INSERT INTO functions VALUES('监控指标')");
    sql_query.exec("INSERT INTO functions VALUES('合约管理')");
    sql_query.exec("INSERT INTO functions VALUES('策略管理')");

    //密码修改：因为所有角色都应有这个功能，所以不放在表格里

    /**************角色表roles************************/
    create_sql =
            "CREATE TABLE IF NOT EXISTS roles ("
            "role_name TEXT PRIMARY KEY"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    sql_query.exec("INSERT INTO roles VALUES('管理员')");
    sql_query.exec("INSERT INTO roles VALUES('交易员')");
    sql_query.exec("INSERT INTO roles VALUES('风控员')");
    sql_query.exec("INSERT INTO roles VALUES('IT')");

    /******************权限表privileges (role_name * function)****************************/
//    "FOREIGN KEY(role_name) REFERENCES roles(role_name),"
//    "FOREIGN KEY(function_name) REFERENCES functions(function_name),"

    sql_query.exec("drop table privileges");
    create_sql =
            "CREATE TABLE IF NOT EXISTS privileges ("
            "role_name TEXT,"
            "function_name TEXT,"
            "PRIMARY KEY (role_name, function_name)"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    if(!sql_query.exec("INSERT INTO privileges VALUES('管理员', '用户管理')")) qDebug() << sql_query.lastError();
    if(!sql_query.exec("INSERT INTO privileges VALUES('交易员', '监控指标')")) qDebug() << sql_query.lastError();
    if(!sql_query.exec("INSERT INTO privileges VALUES('风控员', '风控设置')")) qDebug() << sql_query.lastError();




    /****************用户表users*******************/
    //sql_query.exec("drop table users");
    create_sql =
            "CREATE TABLE IF NOT EXISTS users ("
            "username TEXT PRIMARY KEY,"
            "name TEXT,"
            "role TEXT,"
            "phone TEXT,"
            "email TEXT,"
            "date TEXT,"
            "password TEXT"
            ")";

    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    sql_query.exec("INSERT INTO users VALUES("
                   "'cg487',"
                   "'顾成睿',"
                   "'IT',"
                   "'13570808796',"
                   "'cg487@cornell.edu',"
                   "'2020-08-11',"
                   "'0000'"
                   ")");


    /**************futures期货品种表*****************/
    sql_query.exec("drop table futures");
    create_sql =
            "CREATE TABLE IF NOT EXISTS futures ("
            "future_name TEXT,"
            "future_code TEXT PRIMARY KEY,"
            "exchange TEXT,"
            "category TEXT,"
            "multiplier INT,"
            "mpf FLOAT"
            ")";

    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    sql_query.exec("INSERT INTO futures VALUES("
                   "'铜',"
                   "'cu',"
                   "'上期所',"
                   "'基本金属类',"
                   "5,"
                   "10.0"
                   ")");

    /****************options期权品种表***************/

    /*****************合约表contracts***********************/
    sql_query.exec("drop table future_contracts");
    create_sql =
            "CREATE TABLE IF NOT EXISTS future_contracts("
            "contract_code TEXT PRIMARY KEY, "
            "future_code TEXT,"
            "exchange TEXT,"
            "FOREIGN KEY(future_code) REFERENCES futures(future_code) ON DELETE CASCADE"
            ")";
    //声明foreignkey之前 要先创建这个Key
    //ON DELETE CASCADE 使得删除品种时对应的合约会自动删除

    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError(); //数据库debug语句
    sql_query.exec("INSERT INTO future_contracts VALUES("
                   "'cu2009', "
                   "'cu', "
                   "'上期所'"
                   ")");
    sql_query.exec("INSERT INTO future_contracts VALUES("
                   "'cu2010', "
                   "'cu', "
                   "'上期所'"
                   ")");

    return true;
}

