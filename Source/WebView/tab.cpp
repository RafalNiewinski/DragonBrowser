#include "tab.h"

#define GSEARCH_URL "http://www.google.com/search?q=%1"

tab::tab(QWidget *parent, ConfigManager *configM, QAction *cloudAction, MyWebPage *page):  QWidget(parent)
{
    configLoader = configM;
    webPage = page;
    this->cloudAction = cloudAction;

    createUi();
    createSettings();
    createConnects();
}

tab::~tab()
{
    delete webView;
    delete webPage;
    delete weblayout;
    delete urlAddress;
    delete toolBar;
    delete menulayout;
    delete layout;
}

void tab::createUi()
{
    layout = new QVBoxLayout();
    layout->setMargin(0);

    menulayout= new QHBoxLayout();
    menulayout->setMargin(0);

    weblayout = new QVBoxLayout();
    weblayout->setMargin(0);

    urlAddress = new MyLineEdit();
    urlAddress->setText("");

    suggester = new GoogleSuggest(urlAddress);

    url.setUrl("http://google.pl/");

    webView = new QWebView();
    if(webPage == NULL) webPage = new MyWebPage(configLoader);
    webView->setPage(webPage);
    webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    toolBar = new QToolBar(tr("Navigation"));
    toolBar->setContentsMargins(QMargins(0, 0, 0, 0));
    toolBar->addAction(webView->pageAction(QWebPage::Back));
    toolBar->addAction(webView->pageAction(QWebPage::Forward));
    toolBar->addAction(webView->pageAction(QWebPage::Reload));
    toolBar->addAction(webView->pageAction(QWebPage::Stop));
    toolBar->addWidget(urlAddress);
    //toolBar->addAction(cloudAction);
    menulayout->addWidget(toolBar);
    layout->addLayout(menulayout);

    weblayout->addWidget(webView);
    layout->addLayout(weblayout);

    setLayout(layout);

}

void tab::createSettings()
{
    webView->settings()->setAttribute(QWebSettings::AutoLoadImages, configLoader->AutoLoadImages);
    webView->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, configLoader->DnsPrefetchEnabled);
    webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, configLoader->JavascriptEnabled);
    webView->settings()->setAttribute(QWebSettings::JavaEnabled, configLoader->JavaEnabled);
    webView->settings()->setAttribute(QWebSettings::PluginsEnabled, configLoader->PluginsEnabled);
    webView->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, configLoader->PrivateBrowsingEnabled);
    webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, configLoader->JavascriptCanOpenWindows);
    webView->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, configLoader->JavascriptCanAccessClipboard);
    webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, configLoader->DeveloperExtrasEnabled);
    webView->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled, configLoader->SpatialNavigationEnabled);
    webView->settings()->setAttribute(QWebSettings::LinksIncludedInFocusChain, configLoader->LinksIncludedInFocusChain);
    webView->settings()->setAttribute(QWebSettings::ZoomTextOnly, configLoader->ZoomTextOnly);
    webView->settings()->setAttribute(QWebSettings::PrintElementBackgrounds, configLoader->PrintElementBackgrounds);
    webView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, configLoader->OfflineStorageDatabaseEnabled);
    webView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, configLoader->OfflineWebApplicationCacheEnabled);
    webView->settings()->setAttribute(QWebSettings::LocalStorageEnabled, configLoader->LocalStorageEnabled);
    webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, configLoader->LocalContentCanAccessRemoteUrls);
    webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, configLoader->LocalContentCanAccessFileUrls);
    webView->settings()->setAttribute(QWebSettings::XSSAuditingEnabled, configLoader->XSSAuditingEnabled);
    webView->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, configLoader->AcceleratedCompositingEnabled);
    webView->settings()->setAttribute(QWebSettings::TiledBackingStoreEnabled, configLoader->TiledBackingStoreEnabled);
    webView->settings()->setAttribute(QWebSettings::FrameFlatteningEnabled, configLoader->FrameFlatteningEnabled);
    webView->settings()->setAttribute(QWebSettings::SiteSpecificQuirksEnabled, configLoader->SiteSpecificQuirksEnabled);

    //DATABASE CATALOG PATH TO STORAGE FAVICONS
    webView->settings()->setIconDatabasePath(configLoader->DragonUserDirPath() + "/icons");

    //webView->page()->settings()->setFontFamily(QWebSettings::StandardFont, "Arial");
    //webView->page()->settings()->setFontSize(QWebSettings::DefaultFontSize, 28);

    //////////////////////////////////////////////////////
    /////DOWNLOAD UNSUPPORTED CONTENT STATIC OPTION///////
    webView->page()->setForwardUnsupportedContent(true);//
    //////////////////////////////////////////////////////
    webView->setContextMenuPolicy(Qt::CustomContextMenu);
}

void tab::createConnects()
{
    connect(urlAddress, SIGNAL(returnPressed()), this, SLOT(newUrl()));
    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    //connect(webView, SIGNAL(iconChanged()), this, SLOT(changeIcon()));
    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(chTitle(QString)));
    connect(webView, SIGNAL(iconChanged()), this, SLOT(chIcon()));
    connect(webView, SIGNAL(statusBarMessage(QString)), this, SLOT(statusBarMessage(QString)));
    connect(webView, SIGNAL(selectionChanged()), this, SLOT(selectionChange()));
    connect(webView, SIGNAL(loadStarted()), this, SLOT(loadStart()));
    connect(webView, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinish(bool)));
    connect(webView, SIGNAL(linkClicked(QUrl)), this, SLOT(linkClick(QUrl)));
    connect(webView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    connect(webView->page(), SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(downloadRequest(QNetworkReply*)));
    connect(webView->page(), SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(downloadRequset(QNetworkRequest)));
    connect(webView->page(), SIGNAL(printRequested(QWebFrame*)), this, SLOT(printPage(QWebFrame*)));
}

void tab::urlChanged(QUrl url)
{
    url.setUrl(webView->url().toString());
    urlAddress->setText(url.toString());
}

void tab::newUrl()
{    
    QString adress;
    adress = urlAddress->text();

    if(adress.indexOf(":", 1) != -1 && adress.indexOf(" ") == -1)
    {
        url.setUrl(adress);
        webView->load(url);
        return;
    }
    if(adress.indexOf(".", 1) != -1 && adress.indexOf(" ") == -1)
    {
        adress = "http://"+adress;
        url.setUrl(adress);
        webView->load(url);
        return;
    }

    //IF ADRESS NOT VALID SEARCH WITH GOOGLE
    adress = QString(GSEARCH_URL).arg(adress);
    url.setUrl(adress);
    webView->load(url);
}

void tab::statusBarMessage(QString message)
{
    setStatusTip(message);
}

void tab::selectionChange()
{

}

void tab::loadStart()
{
    urlAddress->setProgress(0);
}

void tab::loadProgress(int progress)
{
    urlAddress->setProgress(progress);
}

void tab::loadFinish(bool ok)
{
    urlAddress->setProgress(100);

    if(configLoader->EnableHistory) HistoryManager::addItem(webView->title(), webView->url());
}

void tab::linkClick(QUrl url)
{
    webView->load(url);
}

void tab::contextMenuRequest(QPoint pos)
{
    clickPos = pos;
    QMenu menu;
    QWebHitTestResult r = webView->page()->mainFrame()->hitTestContent(pos);

    if(!r.linkUrl().isEmpty())
    {
        menu.addAction(tr("Open in New Tab"), this, SLOT(openLinkInNewTab()));
        menu.addAction(webView->pageAction(QWebPage::DownloadLinkToDisk));
        menu.addAction(webView->pageAction(QWebPage::CopyLinkToClipboard));
    }
    if(!r.imageUrl().isEmpty())
    {
        menu.addSeparator();
        menu.addAction(webView->pageAction(QWebPage::DownloadImageToDisk));
        menu.addAction(webView->pageAction(QWebPage::CopyImageToClipboard));
        menu.addAction(webView->pageAction(QWebPage::CopyImageUrlToClipboard));
    }

    menu.addSeparator();
    menu.addAction(webView->pageAction(QWebPage::InspectElement));

    menu.exec(webView->mapToGlobal(pos));
}

void tab::printPage(QWebFrame *frame)
{
    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(this);
    dialog->resize(800, 600);

    connect(dialog, SIGNAL(paintRequested(QPrinter*)), frame, SLOT(print(QPrinter*)));

    dialog->exec();
    dialog->deleteLater();
}

void tab::setCloudStateOnButton(CloudManager::CloudState state)
{

}

//SIGNALS

void tab::chTitle(QString title)
{
    emit chTitleSig(this, title);
}

void tab::chIcon()
{
    emit chIconSig(this, webView->icon());
}

void tab::openLinkInNewTab()
{
    emit openNewTab(webView->page()->mainFrame()->hitTestContent(clickPos).linkUrl());
}

void tab::downloadRequest(QNetworkReply *reply)
{
    emit downloadRequestSig(reply);
}

void tab::downloadRequset(QNetworkRequest request)
{
    emit downloadRequestSig(request);
}
