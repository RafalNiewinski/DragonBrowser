#include "historymanager.h"
#include "Application/dragonbrowser.h"

HistoryManager::HistoryManager()
{
}

void HistoryManager::checkDatabase()
{
    if(!dApp->getDatabaseManager()->getDatabase().tables().contains("history"))
    {
        QSqlQuery query;
        query.exec("CREATE TABLE history (\"id\" INTEGER PRIMARY KEY, \"title\" TEXT, \"url\" TEXT, \"date\" TEXT, \"count\" INT)");
    }
}

bool HistoryManager::addItem(QWebHistoryItem item)
{
    if(addItem(item.title(), item.url())) return true;
    return false;
}

bool HistoryManager::addItem(QString title, QUrl url)
{
    if(addItem(title, url.toString())) return true;
    return false;
}

bool HistoryManager::addItem(QString title, QString url)
{
    if(url.replace(" ", "").isEmpty()) return true;

    QSqlQuery query;
    query.prepare("SELECT id, title, date, count FROM history WHERE url=?");
    query.bindValue(0, url);
    query.exec();

    if(query.next()) //EXISTS
    {
        query.prepare("UPDATE history SET title=?, date=?, count = count + 1 WHERE url=?");
        query.bindValue(0, title);
        query.bindValue(1, QDateTime::currentMSecsSinceEpoch());
        query.bindValue(2, url);

        query.exec();
    }
    else //NOT EXIST
    {
        query.prepare("INSERT INTO history (title, url, date, count) VALUES (?,?,?,1)");
        query.bindValue(0, title);
        query.bindValue(1, url);
        query.bindValue(2, QDateTime::currentMSecsSinceEpoch());

        query.exec();
    }

    return true;
}

QList<HistoryEntry> HistoryManager::fullHistory()
{
    QList<HistoryEntry> history;

    QSqlQuery query;
    query.prepare("SELECT * FROM history");
    query.exec();

    while(query.next())
    {
        HistoryEntry entry;

        entry.title = query.value(1).toString();
        entry.url = query.value(2).toString();
        entry.date = query.value(3).toDateTime();
        entry.count = query.value(4).toInt();

        history.append(entry);
    }

    return history;
}
