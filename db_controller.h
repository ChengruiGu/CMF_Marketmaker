#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#endif // DB_CONTROLLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

//QSqlDatabase database;

QSqlDatabase createDB();
bool createAllTables(QSqlDatabase db);
