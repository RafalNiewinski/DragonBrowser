#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QtWebKit>
#include <QtNetwork>
#include <QFile>
#include <QSettings>

enum StartAction
{
    StartupScreen,
    HomePage,
    RestorePages
};

class ConfigManager
{
public:
    ConfigManager();

    QFile *file;

    //OPTIONS//
    QString homeAddress;

    //WebKit Options
    bool AutoLoadImages;
    bool DnsPrefetchEnabled;
    bool JavascriptEnabled;
    bool JavaEnabled;
    bool PluginsEnabled;
    bool PrivateBrowsingEnabled;
    bool JavascriptCanOpenWindows;
    bool JavascriptCanAccessClipboard;
    bool DeveloperExtrasEnabled;
    bool SpatialNavigationEnabled;
    bool LinksIncludedInFocusChain;
    bool ZoomTextOnly;
    bool PrintElementBackgrounds;
    bool OfflineStorageDatabaseEnabled;
    bool OfflineWebApplicationCacheEnabled;
    bool LocalStorageEnabled;
    bool LocalContentCanAccessRemoteUrls;
    bool LocalContentCanAccessFileUrls;
    bool XSSAuditingEnabled;
    bool AcceleratedCompositingEnabled;
    bool TiledBackingStoreEnabled;
    bool FrameFlatteningEnabled;
    bool SiteSpecificQuirksEnabled;

    //History
    bool EnableHistory;
    //OPTIONS//

    bool loadConfiguration();
    bool saveConfiguration();
    bool loadDefaults();
    QVariant getOption(QString key);
    void setOption(QString key, QVariant value);

    static QString DragonVersion();

    static QString DragonUserDirPath();

    static bool checkSystemDir();

    bool saveSessionData(QList<QString>* urls);
    QList<QString>* restoreSessionData();

private:
    QSettings *settings;
};

#endif // CONFIGMANAGER_H
