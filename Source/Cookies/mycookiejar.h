#ifndef MYCOOKIEJAR_H
#define MYCOOKIEJAR_H

#include <QNetworkCookieJar>

class MyCookieJar : public QNetworkCookieJar
{
public:
    MyCookieJar();

    bool saveAllCookies();
    bool loadAllCookies();
    bool clearOldCookies();
};

#endif // MYCOOKIEJAR_H
