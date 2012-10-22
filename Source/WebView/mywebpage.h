#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include <QWebPage>
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
        //user agent for GOOGLE SEARCH PAGE
        if(url.toString().toStdString().substr(0, 18) == "http://www.google." || url.toString().toStdString().substr(0, 19) == "https://www.google.")
            return QString("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.92 Safari/537.4");


        return QString("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/534.34 (KHTML, like Gecko) DragonBrowser/0.0.1.ALPHA Safari/534.34");
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
