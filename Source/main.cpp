#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QApplication>
#else
        //#include <QtGui/QApplication>
#endif

#include "Application/dragonbrowser.h"
#include "WebView/mainwindow.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow mainwidow;
    //mainwidow.show();

    //return a.exec();


    DragonBrowser app(argc, argv);

    if(app.sendMessage(argv[1])) return 0;

    return app.exec();
}
