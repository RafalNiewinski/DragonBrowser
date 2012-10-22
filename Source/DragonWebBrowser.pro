#-------------------------------------------------
#
# Project created by QtCreator 2012-02-05T15:41:06
#
#-------------------------------------------------

QT       += core gui network

TARGET = DragonWebBrowser
TEMPLATE = app

#TRANSLATIONS = translation_pl.ts

QT += core gui webkit

DEFINES += BUILDDATE=__DATE__
DEFINES += BUILDTIME=__TIME__

HEADERS += \
    Config/pages.h \
    Config/configmanager.h \
    Config/configdialog.h \
    Cookies/mycookiejar.h \
    Download/downloadslot.h \
    Download/downloadmanager.h \
    WebView/tab.h \
    WebView/mainwindow.h \
    WebView/googlesuggest.h \
    WebView/authdialog.h \
    WebView/mywebpage.h \
    WebView/mytabwidget.h

SOURCES += \
    Config/pages.cpp \
    Config/configmanager.cpp \
    Config/configdialog.cpp \
    Cookies/mycookiejar.cpp \
    Download/downloadslot.cpp \
    Download/downloadmanager.cpp \
    WebView/tab.cpp \
    WebView/mainwindow.cpp \
    WebView/googlesuggest.cpp \
    main.cpp \
    WebView/authdialog.cpp \
    WebView/mywebpage.cpp \
    WebView/mytabwidget.cpp
