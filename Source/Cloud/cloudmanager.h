#ifndef CLOUDMANAGER_H
#define CLOUDMANAGER_H

#include <QMenu>
#include <QAction>
#include <QObject>
#include <QApplication>

class CloudManager : public QObject
{
    Q_OBJECT

public:
    enum CloudState
    {
        NONE,
        OK,
        FAIL,
        SYNC
    };

public:
    CloudManager();

    CloudState getCloudState();

private:

    CloudState state;

signals:
    void statusChangedSig(CloudManager::CloudState state);
};

#endif // CLOUDMANAGER_H
