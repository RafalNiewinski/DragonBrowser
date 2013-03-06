#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QtWidgets>
#else
        #include <QtGui>
#endif

class MyTabWidget : public QTabWidget
{
public:
    MyTabWidget();

    void addTab(QWidget *widget, const QString &);
    void removeTab(int index);
    void updateSize();

    QList<QString>* generateAllOpenTabUrls();

private:
    void prepareTabBarSize();
};

#endif // MYTABWIDGET_H
