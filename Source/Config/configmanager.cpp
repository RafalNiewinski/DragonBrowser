#include "configmanager.h"

//DEFINES
#define DRAGON_VERSION "0.0.1.ALPHA"
#define DEVEL_BUILD
//DEFINES

ConfigManager::ConfigManager()
{
    QString env = getenv("HOME");
    file = new QFile(env + "/.DragonWebBrowser/config.cfg");
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
        }
        }


        command.clear();
        argument.clear();
        endofcommand = false;
    }
startAction = RestorePages;
    file->close();
}

QString ConfigManager::DragonVersion()
{
    return DRAGON_VERSION;
}

bool ConfigManager::saveSessionData(QList<QString>* urls)
{
    QString env = getenv("HOME");
    QFile *sessionFile = new QFile(env + "/.DragonWebBrowser/session.last");
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
    QString env = getenv("HOME");
    QFile *sessionFile = new QFile(env + "/.DragonWebBrowser/session.last");
    sessionFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(sessionFile);

    QList<QString> *urls = new QList<QString>();

    while(!in.atEnd())
    {
        urls->append(in.readLine());
    }

    return urls;
}
