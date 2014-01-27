#ifndef DRAGONBROWSER_H
#define DRAGONBROWSER_H

#define dApp DragonBrowser::getInstance()

#include <QApplication>
#include "3rdParty/qtsingleapplication/qtsingleapplication.h"

#include <QList>
#include <QPointer>
#include <QObject>
#include <WebView/mainwindow.h>

#include "Config/configmanager.h"
#include "Config/databasemanager.h"
#include "Cookies/mycookiejar.h"
#include "Download/downloadmanager.h"
#include "API/dragonpluginmanager.h"
#include "History/historymanager.h"
#include "Cloud/cloudmanager.h"

class DragonBrowser : public QtSingleApplication
{
    Q_OBJECT

public:
    explicit DragonBrowser(int &argc, char** argv);

    QList<MainWindow*> getMainWindows();

    static DragonBrowser* getInstance() { return static_cast<DragonBrowser*>(QCoreApplication::instance()); }

    void exitApplication();

    MainWindow* newWindow(QUrl url = QUrl());
    bool removeWindow(MainWindow* window);

    ConfigManager* getConfigManager()                   { return configurationLoader; }
    DatabaseManager* getDatabaseManager()               { return databaseManager; }
    MyCookieJar* getCookieJar()                         { return cookieJar; }
    QNetworkAccessManager* getNetworkAccessManager()    { return nManager; }
    DownloadManager* getDownloadManager()               { return downloadManager; }
    QAuthenticator* getAuthenticator()                  { return authenticator; }
    DragonPluginManager* getDragonPluginManager()       { return pluginManager; }
    HistoryManager* getHistoryManager()                 { return historyManager; }
    CloudManager* getCloudManager()                     { return cloudManager; }

private slots:

    void authorizationRequest(QNetworkReply* reply, QAuthenticator* auth);
    void authorizationConfirm(QString user, QString password);
    void parameterFromAnotherProcess(QString parameter);

private:
    QList <QPointer<MainWindow> > mainWindows;

    ConfigManager *configurationLoader;
    DatabaseManager *databaseManager;
    MyCookieJar *cookieJar;
    QNetworkAccessManager *nManager;
    DownloadManager *downloadManager;
    QAuthenticator *authenticator;
    DragonPluginManager *pluginManager;
    HistoryManager *historyManager;
    CloudManager *cloudManager;

};

#endif // DRAGONBROWSER_H
