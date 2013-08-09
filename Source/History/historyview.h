#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QTreeView>
#include <QStandardItemModel>

#include "historymanager.h"

class HistoryView : public QTreeView
{
public:
    HistoryView();

private:

    void prepareView();

    QStandardItemModel *model;

    QList<QList<QStandardItem*> > items;
};

#endif // HISTORYVIEW_H
