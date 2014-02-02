#ifndef ADDRESSCOMPLETER_H
#define ADDRESSCOMPLETER_H

#include <QObject>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "addressbar.h"

class AddressCompleter : public QObject
{
    Q_OBJECT
public:
    explicit AddressCompleter(AddressBar* bar, QObject *parent = 0);

signals:
    void itemChoosed(QString);

public slots:
    void urlSuggestions(QString url);
    void showSuggestions();

    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void selectionChanged(QModelIndex to);
    void selected();

private:
    AddressBar* addressBar;

    QListView* view;
    QStandardItemModel* model;
};

#endif // ADDRESSCOMPLETER_H
