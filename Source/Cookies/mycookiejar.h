#ifndef MYCOOKIEJAR_H
#define MYCOOKIEJAR_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtNetwork/QNetworkCookieJar>
        #include <QtNetwork/QNetworkCookie>
#else
        #include <QNetworkCookieJar>
#endif

class MyCookieJar : public QNetworkCookieJar
{
public:
    MyCookieJar();

    bool saveAllCookies();
    bool loadAllCookies();
    bool clearOldCookies();
};

#endif // MYCOOKIEJAR_H
