#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QWebHistoryItem>
#include <QSqlQuery>
#include <QUrl>
#include <QList>
#include <QVariant>

#include "Config/databasemanager.h"

struct HistoryEntry
{
public:
    QString title;
    QString url;
    QDateTime date;
    int count;
};

class HistoryManager
{
public:
    HistoryManager();

    static bool addItem(QWebHistoryItem item);
    static bool addItem(QString title, QUrl url);
    static bool addItem(QString title, QString url);

    static QList<HistoryEntry> fullHistory();

private:
    DatabaseManager* dbMan;
};

#endif // HISTORYMANAGER_H
