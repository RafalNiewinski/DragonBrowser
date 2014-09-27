#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWebKitWidgets/QtWebKitWidgets>
#else
        #include <QtWebKit>
#endif

#include "Config/configmanager.h"
#include <QDesktopServices>

class MyWebPage : public QWebPage
{
    Q_OBJECT
public:
    MyWebPage(ConfigManager *cm);
    ~MyWebPage();

    ConfigManager *cfg;

    QString userAgentForUrl(const QUrl &url) const
    {
        #ifdef Q_OS_LINUX
            //user agent for GOOGLE SEARCH PAGE
            if(url.toString().toStdString().substr(0, 18) == "http://www.google." || url.toString().toStdString().substr(0, 19) == "https://www.google.")
                return QString("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.92 Safari/537.4");


            return QString("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/" + qWebKitVersion() + " (KHTML, like Gecko) DragonBrowser/" + ConfigManager::DragonVersion() + " Safari/" + qWebKitVersion());
        #endif

        #ifdef Q_OS_WIN
            //user agent for GOOGLE SEARCH PAGE
            if(url.toString().toStdString().substr(0, 18) == "http://www.google." || url.toString().toStdString().substr(0, 19) == "https://www.google.")
                return QString("Mozilla/5.0 (Windows) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.92 Safari/537.4");


            return QString("Mozilla/5.0 (Windows) AppleWebKit/" + qWebKitVersion() + " (KHTML, like Gecko) DragonBrowser/" + ConfigManager::DragonVersion() + " Safari/" + qWebKitVersion());
        #endif
    }

    QWebPage* createWindow(WebWindowType type)
    {
        MyWebPage *page = new MyWebPage(cfg);
        emit newTabFromPage(page);

        return page;
    }
    //void javaScriptAlert(QWebFrame *originatingFrame, const QString &msg){}
    //bool javaScriptConfirm(QWebFrame *originatingFrame, const QString &msg){}
    //void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID){}
    //bool javaScriptPrompt(QWebFrame *originatingFrame, const QString &msg, const QString &defaultValue, QString *result){}

    bool supportsExtension(Extension extension) const;
    bool extension(Extension extension, const ExtensionOption *option, ExtensionReturn *output);

    void handleUnknownProtocol(const QUrl &url);


signals:

    void newTabFromPage(MyWebPage*);
};

#endif // MYWEBPAGE_H
