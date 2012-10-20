#include <QtGui/QApplication>
#include "WebView/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainwidow;
    mainwidow.show();

    return a.exec();
}
