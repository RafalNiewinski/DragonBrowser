#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtGui>
#include "downloadslot.h"

class DownloadManager : public QMainWindow
{
    Q_OBJECT
public:
    DownloadManager(QWidget *parent = 0);
    
signals:
public slots:

    void startDownload(QUrl url);

private:
    QList <DownloadSlot*> downloads;

    QNetworkAccessManager *manager;

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    QPushButton *addLink;
};
#endif // DOWNLOADMANAGER_H
