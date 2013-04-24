#include "dragonpluginmanager.h"
#include <QDir>
#include <Config/configmanager.h>

DragonPluginManager::DragonPluginManager()
{
    availalblePlugins = new QList<DragonInterface*>();
    enabledPlugins = new QList<DragonInterface*>();
}

bool DragonPluginManager::searchPlugins()
{
    QDir *userPath = new QDir(ConfigManager::DragonUserDirPath() + "/plugins"); //User plugins
    QDir *globalPath = new QDir(qApp->applicationDirPath() + "/plugins"); //Global plugins

    QDir *path = globalPath;
    for(int i=0; i<2;i++) //Search two times (Once for global and once for user plugins)
    {
        foreach(QString fileName, path->entryList(QDir::Files))
        {
            QPluginLoader pluginLoader(path->absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();

            if(plugin)
            {
                DragonInterface *dragonPlugin = qobject_cast<DragonInterface*>(plugin);
                if(dragonPlugin) availalblePlugins->append(dragonPlugin);
            }
        }

        path = userPath;
    }

    delete userPath;
    delete globalPath;
}

bool DragonPluginManager::loadPlugins()
{
}
