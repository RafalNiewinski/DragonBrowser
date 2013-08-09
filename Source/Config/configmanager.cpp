#include "configmanager.h"

//DEFINES
#define DRAGON_VERSION "0.0.1.ALPHA"
#define DEVEL_BUILD
//DEFINES

ConfigManager::ConfigManager()
{
}

bool ConfigManager::loadConfiguration()
{
    file = new QFile(DragonUserDirPath() + "/config.cfg");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(file);

    std::string buf;
    while(!in.atEnd())
    {
        buf = in.readLine().toStdString();
        std::string command;
        std::string argument;
        bool endofcommand = false;
        for(unsigned int i = 0; i < buf.size(); ++i)
        {
            if(buf[i] != ' ' && buf[i] != '=' && buf[i] != '\t')
            {
                if(!endofcommand)
                {
                    command += buf[i];
                }
                else argument += buf[i];
            }
            if(buf[i] == '=')
            {
                endofcommand = true;
            }
        }

        // HANDLING OF SETTINGS
        {
        if(command == "AutoLoadImages") this->AutoLoadImages = atoi(argument.c_str());
        if(command == "DnsPrefetchEnabled") this->DnsPrefetchEnabled = atoi(argument.c_str());
        if(command == "JavascriptEnabled") this->JavascriptEnabled = atoi(argument.c_str());
        if(command == "JavaEnabled") this->JavaEnabled = atoi(argument.c_str());
        if(command == "PluginsEnabled") this->PluginsEnabled = atoi(argument.c_str());
        if(command == "PrivateBrowsingEnabled") this->PrivateBrowsingEnabled = atoi(argument.c_str());
        if(command == "JavascriptCanOpenWindows") this->JavascriptCanOpenWindows = atoi(argument.c_str());
        if(command == "JavascriptCanAccessClipboard") this->JavascriptCanAccessClipboard = atoi(argument.c_str());
        if(command == "DeveloperExtrasEnabled") this->DeveloperExtrasEnabled = atoi(argument.c_str());
        if(command == "SpatialNavigationEnabled") this->SpatialNavigationEnabled = atoi(argument.c_str());
        if(command == "LinksIncludedInFocusChain") this->LinksIncludedInFocusChain = atoi(argument.c_str());
        if(command == "ZoomTextOnly") this->ZoomTextOnly = atoi(argument.c_str());
        if(command == "PrintElementBackgrounds") this->PrintElementBackgrounds = atoi(argument.c_str());
        if(command == "OfflineStorageDatabaseEnabled") this->OfflineStorageDatabaseEnabled = atoi(argument.c_str());
        if(command == "OfflineWebApplicationCacheEnabled") this->OfflineWebApplicationCacheEnabled = atoi(argument.c_str());
        if(command == "LocalStorageEnabled") this->LocalStorageEnabled = atoi(argument.c_str());
        if(command == "LocalContentCanAccessRemoteUrls") this->LocalContentCanAccessRemoteUrls = atoi(argument.c_str());
        if(command == "LocalContentCanAccessFileUrls") this->LocalContentCanAccessFileUrls = atoi(argument.c_str());
        if(command == "XSSAuditingEnabled") this->XSSAuditingEnabled = atoi(argument.c_str());
        if(command == "AcceleratedCompositingEnabled") this->AcceleratedCompositingEnabled = atoi(argument.c_str());
        if(command == "TiledBackingStoreEnabled") this->TiledBackingStoreEnabled = atoi(argument.c_str());
        if(command == "FrameFlatteningEnabled") this->FrameFlatteningEnabled = atoi(argument.c_str());
        if(command == "SiteSpecificQuirksEnabled") this->SiteSpecificQuirksEnabled = atoi(argument.c_str());

        if(command == "StartAction")
        {
            if(argument == "StartupScreen") startAction = StartupScreen;
            if(argument == "HomePage") startAction = HomePage;
            if(argument == "RestorePages") startAction = RestorePages;
            else startAction = StartupScreen;
        }

        //HISTORY
        if(command == "EnableHistory") this->EnableHistory = atoi(argument.c_str());

        }


        command.clear();
        argument.clear();
        endofcommand = false;
    }

    file->close();

    return true;
}

bool ConfigManager::saveConfiguration()
{
    file = new QFile(DragonUserDirPath() + "/config.cfg");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(file);

    // HANDLING OF SETTINGS
    {
    out <<"AutoLoadImages = " <<QString::number(this->AutoLoadImages) <<"\n";
    out <<"DnsPrefetchEnabled = " <<QString::number(this->DnsPrefetchEnabled) <<"\n";
    out <<"JavascriptEnabled = " <<QString::number(this->JavascriptEnabled) <<"\n";
    out <<"JavaEnabled = " <<QString::number(this->JavaEnabled) <<"\n";
    out <<"PluginsEnabled = " <<QString::number(this->PluginsEnabled) <<"\n";
    out <<"PrivateBrowsingEnabled = " <<QString::number(this->PrivateBrowsingEnabled) <<"\n";
    out <<"JavascriptCanOpenWindows = " <<QString::number(this->JavascriptCanOpenWindows) <<"\n";
    out <<"JavascriptCanAccessClipboard = " <<QString::number(this->JavascriptCanAccessClipboard) <<"\n";
    out <<"DeveloperExtrasEnabled = " <<QString::number(this->DeveloperExtrasEnabled) <<"\n";
    out <<"SpatialNavigationEnabled = " <<QString::number(this->SpatialNavigationEnabled) <<"\n";
    out <<"LinksIncludedInFocusChain = " <<QString::number(this->LinksIncludedInFocusChain) <<"\n";
    out <<"ZoomTextOnly = " <<QString::number(this->ZoomTextOnly) <<"\n";
    out <<"PrintElementBackgrounds = " <<QString::number(this->PrintElementBackgrounds) <<"\n";
    out <<"OfflineStorageDatabaseEnabled = " <<QString::number(this->OfflineStorageDatabaseEnabled) <<"\n";
    out <<"OfflineWebApplicationCacheEnabled = " <<QString::number(this->OfflineWebApplicationCacheEnabled) <<"\n";
    out <<"LocalStorageEnabled = " <<QString::number(this->LocalStorageEnabled) <<"\n";
    out <<"LocalContentCanAccessRemoteUrls = " <<QString::number(this->LocalContentCanAccessRemoteUrls) <<"\n";
    out <<"LocalContentCanAccessFileUrls = " <<QString::number(this->LocalContentCanAccessFileUrls) <<"\n";
    out <<"XSSAuditingEnabled = " <<QString::number(this->XSSAuditingEnabled) <<"\n";
    out <<"AcceleratedCompositingEnabled = " <<QString::number(this->AcceleratedCompositingEnabled) <<"\n";
    out <<"TiledBackingStoreEnabled = " <<QString::number(this->TiledBackingStoreEnabled) <<"\n";
    out <<"FrameFlatteningEnabled = " <<QString::number(this->FrameFlatteningEnabled) <<"\n";
    out <<"SiteSpecificQuirksEnabled = " <<QString::number(this->SiteSpecificQuirksEnabled) <<"\n";

    out <<"StartAction = ";
    {
        if(startAction == StartupScreen) out <<"StartupScreen";
        if(startAction == HomePage) out <<"HomePage";
        if(startAction == RestorePages) out <<"RestorePages";
        out <<"\n";
    }

    //HISTORY
    out <<"EnableHistory = " <<QString::number(this->EnableHistory) <<"\n";

    }
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
