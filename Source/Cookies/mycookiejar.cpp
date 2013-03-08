#include "mycookiejar.h"
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QDateTime>
#include <Config/configmanager.h>

MyCookieJar::MyCookieJar()
{
    QNetworkCookieJar();
}

bool MyCookieJar::saveAllCookies()
{
    QFile file(ConfigManager::DragonUserDirPath() + "/cookies.jar");

    file.open(QIODevice::WriteOnly);

    QList<QNetworkCookie> list = this->allCookies();
    QNetworkCookie cookie;

    QString line;

    while(!list.isEmpty())
    {
        cookie = list.first();
        list.pop_front();

        if(cookie.isSessionCookie()) goto stop;

        line  = cookie.domain();
        line += " ";
        line += cookie.expirationDate().toString("ddMMyyyy");
        line += " ";

        if(cookie.isHttpOnly())
            line += '1';
        else
            line += '0';
        line += " ";

        if(cookie.isSecure())
            line += '1';
        else
            line += '0';
        line += " ";

        line += cookie.name();
        line += " ";
        line += cookie.path();
        line += " ";
        line += cookie.value();

        line += "\n";

        file.write(line.toStdString().c_str());

        stop:;
    }

    file.close();

    return true;
}

bool MyCookieJar::loadAllCookies()
{
    QFile file(ConfigManager::DragonUserDirPath() + "/cookies.jar");

    if(file.open(QIODevice::ReadOnly) != true) return true;
    QTextStream st(&file);

    QList<QNetworkCookie> list;
    QNetworkCookie cookie;

    QString line;

    while(!st.atEnd())
    {
        line = "";
        st >> line;
        cookie.setDomain(line);

        line = "";
        st >> line;
        cookie.setExpirationDate(QDateTime::fromString(line, "ddMMyyyy"));

        line = "";
        st >> line;
        if(line == "1") cookie.setHttpOnly(true);
        else           cookie.setHttpOnly(false);

        line = "";
        st >> line;
        if(line == "1") cookie.setSecure(true);
        else           cookie.setSecure(false);

        QByteArray array;
        line = "";
        st >> line;
        array.append(line);
        cookie.setName(array);

        line = "";
        st >> line;
        cookie.setPath(line);

        array = "";
        line = "";
        st >> line;
        array.clear();
        array.append(line);
        cookie.setValue(array);

        list.push_back(cookie);
    }

    this->setAllCookies(list);

    return true;
}

bool MyCookieJar::clearOldCookies()
{
    return true;
}
