#ifndef TAB_H
#define TAB_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QtWidgets>
        #include <QtWebKitWidgets/QtWebKitWidgets>
#else
        #include <QtGui>
        #include <QtWebKit>
#endif

#include "Config/configmanager.h"
#include "googlesuggest.h"
#include "mywebpage.h"
#include "mylineedit.h"
#include "History/historymanager.h"
#include "Cloud/clouddialog.h"
#include "Cloud/cloudmanager.h"

class tab : public QWidget
{
    Q_OBJECT
public:
    tab(QWidget *parent = 0, ConfigManager *configM = NULL, QAction *cloudAction = NULL, MyWebPage *page = NULL);
    ~tab();
    QWebView* webView;
    MyWebPage *webPage;

private:

    QVBoxLayout* layout;
    QHBoxLayout* menulayout;
    QVBoxLayout* weblayout;

    ConfigManager *configLoader;

    QAction *cloudAction;

    QToolBar *toolBar;

    MyLineEdit* urlAddress;
    QUrl url;

    QPoint clickPos;

    GoogleSuggest *suggester;

    void createUi();
    void createSettings();
    void createConnects();

signals:
    void chTitleSig(QWidget* wig, QString title);
    void chIconSig(QWidget* wig, QIcon icon);
    void openNewTab(QUrl url);
    void downloadRequestSig(QNetworkRequest request);
    void downloadRequestSig(QNetworkReply *reply);

public slots:
    void chTitle(QString title);
    void chIcon();
    void downloadRequest(QNetworkReply *reply);
    void downloadRequset(QNetworkRequest request);
    void openLinkInNewTab();

    void newUrl();
    void urlChanged(QUrl url);
    void statusBarMessage(QString message);
    void selectionChange();
    void loadStart();
    void loadProgress(int progress);
    void loadFinish(bool ok);
    void linkClick(QUrl url);
    void contextMenuRequest(QPoint pos);
    void printPage(QWebFrame* frame);
    void setCloudStateOnButton(CloudManager::CloudState state);
};

#endif // TAB_H
