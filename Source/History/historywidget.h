#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QtGui>

#include "historyview.h"

class HistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryWidget(QWidget *parent = 0);
    
private:
    QVBoxLayout *layout;
    HistoryView *historyView;
};

#endif // HISTORYWIDGET_H
