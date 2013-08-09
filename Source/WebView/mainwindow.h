#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QtWidgets>
#else

#endif

#include <QtWebKit>
#include "tab.h"

#include "authdialog.h"
#include "mytabwidget.h"
#include "library.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QWidget* centralWidget;
    QVBoxLayout* layout;

    QMenu* filemenu;
    QAction* newTabAction;
    QAction* closeTabAction;
    QAction* newWindowAction;
    QAction* saveAsImageAction;
    QAction* printPageAction;
    QAction* quitAction;

    QMenu *viewMenu;
    QAction* viewSourceAction;

    QMenu* historyMenu;
    QAction* historyManagerAction;

    QMenu *toolsMenu;
    QAction *downloadManagerAction;
    QAction *preferencesAction;

    QMenu *cloudMenu;
    //STATUS NONE
    QAction *cloudConnectAction;
    //STATUS OK, FAIL, SYNC
    QAction *cloudDisplayStatusAction;
    QAction *manageCloudAction;
    QAction *disconnectCloudAction;

    QMenu *helpMenu;
    QAction *aboutAction;

    MyTabWidget* tabs;
    QToolButton* addTabButton;

    QAction *cloudAction;

    void createFileActions();
    void createMenus();
    void createUi();
    void createConnects();

public slots:
    void createCustomTab(QWidget* widget, QString title);
    void createPluginTab(QWidget* plugin, QString title);

    void saveAsImage();
    tab* createStandardTab();
    void createTabWithUrl(QUrl url);
    void deleteTab(int index);
    void deleteCurrentTab();
    void newWindow();
    void setTitle(int id);
    void tabName(QWidget* id, QString title);
    void tabIcon(QWidget* id, QIcon icon);
    void viewSource();
    void slotSourceDownloaded();
    void highlightAllLinks();
    void removeObjectElements();
    void removeEmbeddedElements();
    void openPreferences();
    void exitWindow();
    virtual void closeEvent(QCloseEvent *);
    virtual void resizeEvent(QResizeEvent *);
    void showAbout();
    void showDownloadManager();
    void showLibraryHistory();
    void printRequest();
    void openNewTabFromPage(MyWebPage* definiedPage);
    void createConfigForNewStandardTab(tab* page);
    bool saveSession();
    bool restoreSession();
    void cloudStatusChanged(CloudManager::CloudState state);
    void cloudActionCalled();

};

#endif // MAINWINDOW_H
