#ifndef DRAGONINTERFACE_H
#define DRAGONINTERFACE_H

#define INTERFACE_VERSION "1"

#include <QString>
#include <QList>
#include <QAction>

class DragonInterface
{
public:
    virtual ~DragonInterface() = 0;

private:
    bool haveTab;
    bool haveMenu;

    QString pluginName;
    QString pluginAuthor;
    QString pluginStoreId;
    QString pluginVersion;
    QList<QAction*>* menuActions;
    QWidget *tabContent;

signals:
    virtual void notificationRequset(QString text) = 0;
    virtual void stopRequest() = 0;
    virtual void addonRequest(QString addonStoreId) = 0;

public:
    virtual void Initialize() = 0;
    virtual bool installPlugin() = 0;
    virtual void timeTask() = 0;
    virtual void uninstallPlugin() = 0;
    virtual void stopPlugin() = 0;

    virtual QString getName() = 0;
    virtual QString getAuthor() = 0;
    virtual QString getStoreId() = 0;
    virtual QString getVersion() = 0;
    virtual QWidget* getTabWidget() = 0;
    virtual QList<QAction*>* generateActions() = 0;

    virtual bool menuExist() = 0;
    virtual bool tabWidgetExist() = 0;

};

Q_DECLARE_INTERFACE(DragonInterface, "org.Dragon.Interface/1")

#endif // DRAGONINTERFACE_H
