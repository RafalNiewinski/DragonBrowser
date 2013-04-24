#ifndef DRAGONPLUGINMANAGER_H
#define DRAGONPLUGINMANAGER_H

#define INTERFACE_VERSION 1
#define MIN_PLUGIN_INTERFACE 1

#include <API/dragoninterface.h>
#include <QList>

class DragonPluginManager
{
public:
    DragonPluginManager();

    bool searchPlugins();
    bool loadPlugins();

private:
    QList<DragonInterface*>* availalblePlugins;
    QList<DragonInterface*>* enabledPlugins;
};

#endif // DRAGONPLUGINMANAGER_H
