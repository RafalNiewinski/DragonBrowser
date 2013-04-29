#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class DatabaseManager
{
public:
    DatabaseManager();

    bool openConnection();
    QSqlError getError();
    QSqlQuery execute(QString query);

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
