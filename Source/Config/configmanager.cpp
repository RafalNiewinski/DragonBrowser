#include "configmanager.h"

//DEFINES
#define DRAGON_VERSION "0.0.1.ALPHA"
#define DEVEL_BUILD
//DEFINES

ConfigManager::ConfigManager()
{
    settings = new QSettings(DragonUserDirPath() + "/config.cfg", QSettings::IniFormat);
}

bool ConfigManager::loadConfiguration()
{
    if(settings->allKeys().isEmpty()) return loadDefaults();

    homeAddress = getOption("HomeAddress").toString();
    EnableHistory = getOption("EnableHistory").toBool();

    return true;
}

bool ConfigManager::saveConfiguration()
{
    settings->sync();

    if(settings->status() ==  QSettings::NoError) return true;
    else return true;
}

bool ConfigManager::loadDefaults()
{
    setOption("AutoLoadImages", true);
    setOption("DnsPrefetchEnabled", false);
    setOption("JavascriptEnabled", true);
    setOption("JavaEnabled", true);
    setOption("PluginsEnabled", true);
    setOption("PrivateBrowsingEnabled", false);
    setOption("JavascriptCanOpenWindows", true);
    setOption("JavascriptCanAccessClipboard", true);
    setOption("DeveloperExtrasEnabled", true);
    setOption("SpatialNavigationEnabled", false);
    setOption("LinksIncludedInFocusChain", true);
    setOption("ZoomTextOnly", false);
    setOption("PrintElementBackgrounds", true);
    setOption("OfflineStorageDatabaseEnabled", true);
    setOption("OfflineWebApplicationCacheEnabled", true);
    setOption("LocalStorageEnabled", true);
    setOption("LocalContentCanAccessRemoteUrls", true);
    setOption("LocalContentCanAccessFileUrls", true);
    setOption("XSSAuditingEnabled", false);
    setOption("AcceleratedCompositingEnabled", true);
    setOption("TiledBackingStoreEnabled", false);
    setOption("FrameFlatteningEnabled", false);
    setOption("SiteSpecificQuirksEnabled", true);

    ///////////////////////////////////////////////////////////////

    setOption("StartAction", "StartupScreen");

    EnableHistory = true;
    setOption("EnableHistory", true);

    if(saveConfiguration()) return true;
    else return false;
}

QVariant ConfigManager::getOption(QString key)
{
    return settings->value(key, QVariant(-1));
}

void ConfigManager::setOption(QString key, QVariant value)
{
    settings->setValue(key, value);
}

QString ConfigManager::DragonVersion()
{
    return DRAGON_VERSION;
}

QString ConfigManager::DragonUserDirPath()
{
#ifdef Q_OS_LINUX
    QString env = getenv("HOME");
    return env + "/.DragonWebBrowser";
#endif
}

bool ConfigManager::checkSystemDir()
{
    #ifdef Q_OS_LINUX

    if(QDir(DragonUserDirPath()).exists() != true)
        if(QDir().mkdir(DragonUserDirPath()) != true) return false;

    if(QDir(DragonUserDirPath() + "/plugins").exists() != true)
        if(QDir().mkdir(DragonUserDirPath() + "/plugins") != true) return false;

    if(QDir(DragonUserDirPath() + "/icons").exists() != true)
        if(QDir().mkdir(DragonUserDirPath() + "/icons") != true) return false;

    return true;

    #endif
}

bool ConfigManager::saveSessionData(QList<QString>* urls)
{
    QFile *sessionFile = new QFile(DragonUserDirPath() + "/session.last");
    sessionFile->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(sessionFile);

    for(int i=0; i < urls->length(); i++)
    {
        out << urls->at(i) <<"\n";
    }

    sessionFile->close();

    return true;
}

QList<QString>* ConfigManager::restoreSessionData()
{
    QFile *sessionFile = new QFile(DragonUserDirPath() + "/session.last");
    sessionFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(sessionFile);

    QList<QString> *urls = new QList<QString>();

    while(!in.atEnd())
    {
        urls->append(in.readLine());
    }

    return urls;
}
