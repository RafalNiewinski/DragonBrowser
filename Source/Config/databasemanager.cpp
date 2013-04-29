#include "databasemanager.h"
#include "configmanager.h"

DatabaseManager::DatabaseManager()
{
}

bool DatabaseManager::openConnection()
{
    database = QSqlDatabase::addDatabase("QSQLITE"); // Find QSLite driver

    database.setDatabaseName(ConfigManager::DragonUserDirPath() + "/userdata.db");

    return database.open();
}

QSqlError DatabaseManager::getError()
{
    return database.lastError();
}

QSqlQuery DatabaseManager::execute(QString query)
{
    return database.exec(query);
}
