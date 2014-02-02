#-------------------------------------------------
#
# Project created by QtCreator 2012-02-05T15:41:06
#
#-------------------------------------------------

contains(QT_VERSION, 4.6)
{
    QT       += core gui network webkit sql
}
contains(QT_VERSION, 5.0)
{
    QT       += core widgets network webkit webkitwidgets sql
}

TARGET = DragonWebBrowser
TEMPLATE = app

#TRANSLATIONS = translation_pl.ts

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
    WebView/authdialog.h \
    WebView/mywebpage.h \
    WebView/mytabwidget.h \
    API/dragoninterface.h \
    API/dragonpluginmanager.h \
    Config/databasemanager.h \
    History/historymanager.h \
    3rdParty/fancytabwidget.h \
    3rdParty/stylehelper.h \
    WebView/library.h \
    History/historywidget.h \
    History/historyview.h \
    Cloud/cloudmanager.h \
    Cloud/clouddialog.h \
    Application/dragonbrowser.h \
    3rdParty/qtsingleapplication/qtlockedfile.h \
    3rdParty/qtsingleapplication/qtsinglecoreapplication.h \
    3rdParty/qtsingleapplication/qtsingleapplication.h \
    3rdParty/qtsingleapplication/qtlocalpeer.h \
    Navigation/addressbar.h \
    Navigation/addresscompleter.h \
    Navigation/addresscompleterdelegate.h

SOURCES += \
    Config/pages.cpp \
    Config/configmanager.cpp \
    Config/configdialog.cpp \
    Cookies/mycookiejar.cpp \
    Download/downloadslot.cpp \
    Download/downloadmanager.cpp \
    WebView/tab.cpp \
    WebView/mainwindow.cpp \
    main.cpp \
    WebView/authdialog.cpp \
    WebView/mywebpage.cpp \
    WebView/mytabwidget.cpp \
    API/dragonpluginmanager.cpp \
    Config/databasemanager.cpp \
    History/historymanager.cpp \
    3rdParty/fancytabwidget.cpp \
    3rdParty/stylehelper.cpp \
    WebView/library.cpp \
    History/historywidget.cpp \
    History/historyview.cpp \
    Cloud/cloudmanager.cpp \
    Cloud/clouddialog.cpp \
    Application/dragonbrowser.cpp \
    3rdParty/qtsingleapplication/qtlockedfile_win.cpp \
    3rdParty/qtsingleapplication/qtlockedfile_unix.cpp \
    3rdParty/qtsingleapplication/qtlockedfile.cpp \
    3rdParty/qtsingleapplication/qtsingleapplication.cpp \
    3rdParty/qtsingleapplication/qtlocalpeer.cpp \
    Navigation/addressbar.cpp \
    Navigation/addresscompleter.cpp \
    Navigation/addresscompleterdelegate.cpp
