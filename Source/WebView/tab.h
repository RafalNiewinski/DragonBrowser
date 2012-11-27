#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QtGui>
#include <QtWebKit>
#include "Config/configmanager.h"
#include "googlesuggest.h"
#include "mywebpage.h"

class tab : public QWidget
{
    Q_OBJECT
public:
    tab(QWidget *parent = 0, ConfigManager *configM = NULL, MyWebPage *page = NULL);
    ~tab();
    QWebView* webView;
    MyWebPage *webPage;
private:

    QVBoxLayout* layout;
    QHBoxLayout* menulayout;
    QVBoxLayout* weblayout;

    ConfigManager *configLoader;

    QToolBar *toolBar;

    QLineEdit* urlAdress;
    QUrl url;

    QPoint clickPos;

    GoogleSuggest *suggester;

    //QLabel* status;
    QString num; //dla slotu loadProgress(int progress)

    void createUi();
    void createSettings();
    void createConnects();

signals:
    void chTitleSig(QWidget* wig, QString title);
    void openNewTab(QUrl url);
    void downloadRequestSig(QNetworkRequest request);
    void downloadRequestSig(QNetworkReply *reply);

public slots:
    void chTitle(QString title);
    void downloadRequest(QNetworkReply *reply);
    void downloadRequset(QNetworkRequest request);
    void openLinkInNewTab();

    void newUrl();
    void urlChanged(QUrl url);
    void changeIcon();
    void titleChange(QString title);
    void statusBarMessage(QString message);
    void selectionChange();
    void loadStart();
    void loadProgress(int progress);
    void loadFinish(bool ok);
    void linkClick(QUrl url);
    void contextMenuRequest(QPoint pos);
    void printPage(QWebFrame* frame);
};

#endif // TAB_H
