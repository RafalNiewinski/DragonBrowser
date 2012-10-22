#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include <QtWebKit>
#include "tab.h"
#include "Config/configmanager.h"
#include "Cookies/mycookiejar.h"
#include "Download/downloadmanager.h"
#include "authdialog.h"
#include "mytabwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QWidget* centralWidget;
    QVBoxLayout* layout;

    ConfigManager *configurationLoader;

    MyCookieJar *cookieJar;
    QNetworkAccessManager *nManager;

    DownloadManager *downloadManager;

    QMenu* filemenu;
    QAction* newTabAction;
    QAction* closeTabAction;
    QAction* newWindowAction;
    QAction* saveAsImageAction;
    QAction* printPageAction;
    QAction* quitAction;

    QMenu *viewMenu;
    QAction* viewSourceAction;

    QMenu *toolsMenu;
    QAction *downloadManagerAction;
    QAction *preferencesAction;

    QMenu *helpMenu;
    QAction *aboutAction;

    MyTabWidget* tabs;
    QToolButton* addTabButton;

    QAuthenticator *authenticator;

    void createFileActions();
    void createMenus();
    void createUi();
    void createConnects();

    bool checkSystemDir();

public slots:
    void createCustomTab(QWidget* widget, QString title);
    void createPluginTab(QWidget* plugin, QString title);

private slots:
    void saveAsImage();
    tab* createStandardTab();
    void createTabWithUrl(QUrl url);
    void deleteTab(int index);
    void deleteCurrentTab();
    void newWindow();
    void setTitle(int id);
    void tabName(QWidget* id, QString title);
    void viewSource();
    void slotSourceDownloaded();
    void highlightAllLinks();
    void removeObjectElements();
    void removeEmbeddedElements();
    void openPreferences();
    void exitApplication();
    virtual void closeEvent(QCloseEvent *);
    virtual void resizeEvent(QResizeEvent *);
    void showAbout();
    void showDownloadManager();
    void authorizationRequest(QNetworkReply* reply,QAuthenticator* auth);
    void authorizationConfirm(QString user, QString password);
    void printRequest();
    void openNewTabFromPage(MyWebPage* definiedPage);
    void createConfigForNewStandardTab(tab* page);

};

#endif // MAINWINDOW_H
