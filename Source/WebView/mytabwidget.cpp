#include "mytabwidget.h"

#define MAXIMUM_TAB_WIDTH 250

MyTabWidget::MyTabWidget()
{
    QTabWidget();
}

void MyTabWidget::addTab(QWidget *widget, const QString &title)
{
    QTabWidget::addTab(widget, title);
    prepareTabBarSize();
}

void MyTabWidget::removeTab(int index)
{
    QTabWidget::removeTab(index);
    prepareTabBarSize();
}

void MyTabWidget::updateSize()
{
    prepareTabBarSize();
}

void MyTabWidget::prepareTabBarSize()
{
    int size = this->tabBar()->size().width() / this->count();
    if(size > MAXIMUM_TAB_WIDTH) this->tabBar()->setStyleSheet(QString("QTabBar::tab { width: %1px }").arg(MAXIMUM_TAB_WIDTH));
    else this->tabBar()->setStyleSheet(QString("QTabBar::tab { width: %1px }").arg(size));
}