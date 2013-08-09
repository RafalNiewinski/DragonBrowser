#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>
#include <QMainWindow>
#include <QtGui>

#include "3rdParty/fancytabwidget.h"
#include "History/historywidget.h"

class Library : public QMainWindow
{
    Q_OBJECT
public:
    Library(int element);

private:
    QWidget *mainWidget;

    QVBoxLayout *layout;

    FancyTabWidget *fancyTab;

    HistoryWidget *historyWidget;
};

#endif // LIBRARY_H
