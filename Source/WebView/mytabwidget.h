#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QtGui>

class MyTabWidget : public QTabWidget
{
public:
    MyTabWidget();

    void addTab(QWidget *widget, const QString &);
    void removeTab(int index);
    void updateSize();

private:
    void prepareTabBarSize();
};

#endif // MYTABWIDGET_H
