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
            "function_name TEXT"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();

    /**************角色表roles************************/
    create_sql =
            "CREATE TABLE IF NOT EXISTS roles ("
            "role_name TEXT"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();

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
    sql_query.exec(create_sql);
    if(!sql_query.isActive()) return false;
    sql_query.exec("INSERT INTO users VALUES("
                   "'cg487',"
                   "'顾成睿',"
                   "'IT',"
                   "'13570808796',"
                   "'cg487@cornell.edu',"
                   "'2020-08-11',"
                   "'0000'"
                   ")");
    //db.close();

    /**************futures期货品种表*****************/
    //sql_query.exec("drop table futures");
    create_sql =
            "CREATE TABLE IF NOT EXISTS futures ("
            "future_name TEXT,"
            "future_code TEXT PRIMARY KEY,"
            "exchange TEXT,"
            "category TEXT,"
            "multiplier INT,"
            "mpf REAL"
            ")";
    sql_query.exec(create_sql);
    if(!sql_query.isActive()) return false;
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
    //sql_query.exec("drop table future_contracts");
    create_sql =
            "CREATE TABLE IF NOT EXISTS future_contracts("
            "contract_code TEXT PRIMARY KEY, "
            "future_code TEXT,"
            "exchange TEXT,"
            "FOREIGN KEY(future_code) REFERENCES futures(future_code)"
            ")";
    //声明foreignkey之前 要先创建这个Key

    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError(); //数据库debug语句
    if(!sql_query.isActive()) qWarning("shit happens");
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

