#include "db_controller.h"
#include <QMessageBox>
//参考 https://www.cnblogs.com/xia-weiwen/archive/2017/05/04/6806709.html
#include <QtDebug>
#include <QFile>

//https://stackoverflow.com/questions/1601151/how-do-i-check-in-sqlite-whether-a-table-exists

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

    //    /*****************功能表functions***************/
    //    //这个表暂时没用上
    //    create_sql =
    //            "CREATE TABLE IF NOT EXISTS functions ("
    //            "function_name TEXT PRIMARY KEY"
    //            ")";
    //    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    //    sql_query.exec("INSERT INTO functions VALUES('用户管理')");
    //    sql_query.exec("INSERT INTO functions VALUES('角色管理')");
    //    sql_query.exec("INSERT INTO functions VALUES('品种设置')");
    //    sql_query.exec("INSERT INTO functions VALUES('做市权限设置')");
    //    sql_query.exec("INSERT INTO functions VALUES('风控设置')");
    //    sql_query.exec("INSERT INTO functions VALUES('监控指标')");
    //    sql_query.exec("INSERT INTO functions VALUES('合约管理')");
    //    sql_query.exec("INSERT INTO functions VALUES('策略管理')");

    //    //密码修改：因为所有角色都应有这个功能，所以不放在表格里

    //    /**************角色表roles************************/
    //    //这个表暂时没用上
    //    create_sql =
    //            "CREATE TABLE IF NOT EXISTS roles ("
    //            "role_name TEXT PRIMARY KEY"
    //            ")";
    //    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    //    sql_query.exec("INSERT INTO roles VALUES('管理员')");
    //    sql_query.exec("INSERT INTO roles VALUES('交易员')");
    //    sql_query.exec("INSERT INTO roles VALUES('风控员')");
    //    sql_query.exec("INSERT INTO roles VALUES('IT')");

    /******************权限表privileges (role_name * function)****************************/
    //    "FOREIGN KEY(role_name) REFERENCES roles(role_name),"
    //    "FOREIGN KEY(function_name) REFERENCES functions(function_name),"

    //sql_query.exec("drop table privileges");
    create_sql =
            "CREATE TABLE IF NOT EXISTS privileges ("
            "role_name TEXT,"
            "function_name TEXT,"
            "PRIMARY KEY (role_name, function_name)"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();
    sql_query.exec("INSERT INTO privileges VALUES('管理员', '用户管理')");
    sql_query.exec("INSERT INTO privileges VALUES('交易员', '监控指标')");
    sql_query.exec("INSERT INTO privileges VALUES('风控员', '风控设置')");




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
                   "'管理员',"
                   "'13570808796',"
                   "'cg487@cornell.edu',"
                   "'2020-08-11',"
                   "'0000'"
                   ")");


    /************** futures 期货品种表 *****************/
    //sql_query.exec("drop table futures");
    create_sql =
            "CREATE TABLE IF NOT EXISTS futures ("
            "future_name TEXT,"
            "future_code TEXT PRIMARY KEY,"
            "exchange TEXT,"
            "category TEXT,"
            "multiplier INT,"
            "mpf TEXT"
            ")";
    //  mpf应该是小数,但sqlite数据库有精度丢失的问题,0.02会变成0.1999999999999,无法解决


    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError();

    //添加文件请点击resources.qrc 添加后文件路径前要加冒号
    QFile file(":/product_source.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file product_source.txt!";
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        sql_query.exec(line);
    }


    /****************options期权品种表***************/
    //期权部分暂未开发

    /***************** 期货合约表 future_contracts ***********************/
    //sql_query.exec("drop table future_contracts");
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

    /********** 策略表 strategies ******************/
    //sql_query.exec("drop table strategies");
    create_sql =
            "CREATE TABLE IF NOT EXISTS strategies("
            "strategy_name TEXT PRIMARY KEY"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError(); //数据库debug语句
    //sql_query.exec("INSERT INTO strategies VALUES('突破买入.exe')");

    /********** 策略-合约表 strategy_contract ***************/
    //sql_query.exec("drop table strategy_contracts");
    create_sql =
            "CREATE TABLE IF NOT EXISTS strategy_contracts("
            "strategy_name TEXT, "
            "contract_code TEXT,"
            "FOREIGN KEY(strategy_name) REFERENCES strategies(strategy_name) ON DELETE CASCADE,"
            "FOREIGN KEY(contract_code) REFERENCES future_contracts(contract_code) ON DELETE CASCADE,"
            "PRIMARY KEY(strategy_name, contract_code)"
            ")";
    if(!sql_query.exec(create_sql)) qDebug() << sql_query.lastError(); //数据库debug语句
    //sql_query.exec("INSERT INTO strategy_contracts VALUES('突破买入.exe', 'cu2009')");

    /********** 参数表 parameters ******************/

    /********** 参数-策略表 parameter-strategy ***************/

    return true;
}

