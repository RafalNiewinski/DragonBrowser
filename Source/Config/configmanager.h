#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QtWebKit>
#include <QtNetwork>
#include <QFile>

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

    StartAction startAction;
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
};

#endif // CONFIGMANAGER_H
