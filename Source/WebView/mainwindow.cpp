#include "mainwindow.h"
#include <string>
#include <iostream>
#include <QtGlobal>
#include "tab.h"
#include "Config/configdialog.h"
#include "Application/dragonbrowser.h"

MainWindow::MainWindow()
{
    setWindowTitle("Dragon Web Browser Alpha");
    setWindowIcon(QIcon("/path/window_icon.png"));

    createFileActions();
    createMenus();
    createUi();
    createConnects();

    setMinimumSize(160, 160);
    //this->showMaximized();
}

void MainWindow::createFileActions()
{
    newTabAction = new QAction(tr("New tab"), this);
    newTabAction->setShortcut(Qt::CTRL + Qt::Key_T);
    connect(newTabAction, SIGNAL(triggered()), this, SLOT(createStandardTab()));

    closeTabAction = new QAction(tr("Close tab"), this);
    closeTabAction->setShortcut(Qt::CTRL + Qt::Key_W);
    connect(closeTabAction, SIGNAL(triggered()), this, SLOT(deleteCurrentTab()));

    newWindowAction = new QAction(tr("New window"), this);
    newWindowAction->setShortcut(Qt::CTRL + Qt::Key_N);
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    saveAsImageAction = new QAction(tr("Save screenshoot of page"), this);
    connect(saveAsImageAction, SIGNAL(triggered()), this, SLOT(saveAsImage()));
    //saveAsImageAction->setShortcut();

    printPageAction = new QAction(tr("Print page"), this);
    printPageAction->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(printPageAction, SIGNAL(triggered()), this, SLOT(printRequest()));

    quitAction = new QAction(tr("Quit"), this);
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitWindow()));

    viewSourceAction = new QAction(tr("Source code"), this);
    connect(viewSourceAction, SIGNAL(triggered()), SLOT(viewSource()));

    resetZoomAction = new QAction(tr("Reset zoom"), this);
    resetZoomAction->setShortcut(Qt::CTRL + Qt::Key_0);
    connect(resetZoomAction, SIGNAL(triggered()), this, SLOT(resetZoom()));

    zoomInAction = new QAction(tr("Zoom in"), this);
    zoomInAction->setShortcut(Qt::CTRL + Qt::Key_Plus);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("Zoom out"), this);
    zoomOutAction->setShortcut(Qt::CTRL + Qt::Key_Minus);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    historyManagerAction = new QAction(tr("History manager"), this);
    connect(historyManagerAction, SIGNAL(triggered()), this, SLOT(showLibraryHistory()));

    downloadManagerAction = new QAction(tr("Download manager"), this);
    connect(downloadManagerAction, SIGNAL(triggered()), this, SLOT(showDownloadManager()));

    preferencesAction = new QAction(tr("Preferences"), this);
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(openPreferences()));

    cloudConnectAction = new QAction(tr("Cloud"), this);

    cloudDisplayStatusAction = new QAction(tr("Status"), this);

    manageCloudAction = new QAction(tr("Manage cloud"), this);

    disconnectCloudAction = new QAction(tr("Disconnect from cloud"), this);

    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void MainWindow::createMenus()
{
    filemenu = new QMenu(tr("File"), this);
    menuBar()->addMenu(filemenu);

    filemenu->addAction(newTabAction);
    filemenu->addAction(closeTabAction);
    filemenu->addAction(newWindowAction);
    filemenu->addAction(saveAsImageAction);
    filemenu->addAction(printPageAction);
    filemenu->addSeparator();
    filemenu->addAction(quitAction);

    viewMenu = new QMenu(tr("View"), this);
    menuBar()->addMenu(viewMenu);
    viewMenu->addAction(viewSourceAction);
    viewMenu->addSeparator();
    viewMenu->addAction(resetZoomAction);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    //viewMenu->addAction(tr("Highlight all links"), this, SLOT(highlightAllLinks()));
    //viewMenu->addAction(tr("Remove all object elements"), this, SLOT(removeObjectElements()));
    //viewMenu->addAction(tr("Remove all embedded elements"), this, SLOT(removeEmbeddedElements()));

    historyMenu = new QMenu(tr("History"), this);
    menuBar()->addMenu(historyMenu);
    historyMenu->addAction(historyManagerAction);

    toolsMenu = new QMenu(tr("Tools"), this);
    menuBar()->addMenu(toolsMenu);
    toolsMenu->addAction(downloadManagerAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(preferencesAction);

    cloudMenu = new QMenu(tr("Cloud"), this);
    //generateCloudMenuActions();

    helpMenu = new QMenu(tr("Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(tr("About Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::createUi()
{
    layout = new QVBoxLayout();
    centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    layout->setMargin(0);

    addTabButton = new QToolButton(this);

    addTabButton->setText("+");
    addTabButton->setCursor(Qt::ArrowCursor);
    addTabButton->setAutoRaise(true);
    addTabButton->setToolTip(tr("New tab"));

    tabs = new MyTabWidget();
    tabs->setTabsClosable(true);
    tabs->setMovable(true);
    tabs->setDocumentMode(true);
    tabs->setUsesScrollButtons(false);
    tabs->setElideMode(Qt::ElideRight);
    tabs->setCornerWidget(addTabButton, Qt::TopRightCorner);

    layout->addWidget(tabs);


    cloudAction = new QAction(QIcon(qApp->applicationDirPath() + "/Content/ICONS/cloud.png"), "", this);
}

void MainWindow::createConnects()
{
    connect(addTabButton, SIGNAL(clicked()), this, SLOT(createStandardTab()));
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteTab(int)));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(setTitle(int)));
    connect(cloudAction, SIGNAL(triggered()), this, SLOT(cloudActionCalled()));
}

void MainWindow::saveAsImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as image..."), QDir::homePath(), tr("PNG Image Files (*.png)"));
    tab *tmp = (tab*)tabs->currentWidget();

    QRect oryginal = tmp->webView->geometry();

    tmp->webView->setGeometry(QRect(QPoint(0, 0), tmp->webView->page()->mainFrame()->contentsSize()));

    QImage image = QPixmap::grabWidget(tmp->webView).toImage();

    tmp->webView->setGeometry(oryginal);

    image.save(fileName, "PNG");

}

tab* MainWindow::createStandardTab()
{
    tab* page;
    page = new tab(0, dApp->getConfigManager(), cloudAction);
    tabs->addTab(page, "Blank tab");
    createConfigForNewStandardTab(page);

    return page;
}

void MainWindow::createTabWithUrl(QUrl url)
{
    tab* page = createStandardTab();
    page->webView->load(url);
}

void MainWindow::openNewTabFromPage(MyWebPage *definiedPage)
{
    tab* page;
    page = new tab(0, dApp->getConfigManager(), cloudAction, definiedPage);
    tabs->addTab(page, "Blank tab");
    createConfigForNewStandardTab(page);
}

void MainWindow::createCustomTab(QWidget *widget, QString title)
{}

void MainWindow::createPluginTab(QWidget *plugin, QString title)
{}

void MainWindow::createConfigForNewStandardTab(tab *page)
{
    page->webView->page()->setNetworkAccessManager(dApp->getNetworkAccessManager());

    connect(page, SIGNAL(chTitleSig(QWidget*,QString)), this, SLOT(tabName(QWidget*,QString)));
    connect(page, SIGNAL(chIconSig(QWidget*,QIcon)), this, SLOT(tabIcon(QWidget*,QIcon)));
    connect(page, SIGNAL(downloadRequestSig(QNetworkRequest)), dApp->getDownloadManager(), SLOT(startDownload(QNetworkRequest)));
    connect(page, SIGNAL(downloadRequestSig(QNetworkReply*)), dApp->getDownloadManager(), SLOT(startDownload(QNetworkReply*)));
    connect(page, SIGNAL(openNewTab(QUrl)), this, SLOT(createTabWithUrl(QUrl)));
    connect(page->webPage, SIGNAL(newTabFromPage(MyWebPage*)), this, SLOT(openNewTabFromPage(MyWebPage*)));
    tabs->setCurrentIndex(tabs->indexOf(page));
}

void MainWindow::deleteTab(int index)
{
    if(tabs->count() == 1) exitWindow();
    else
    {
        QWidget *tabwidget = tabs->widget(index);
        tabs->removeTab(index);
        delete tabwidget;
    }
}

void MainWindow::deleteCurrentTab()
{
    deleteTab(tabs->currentIndex());
}

void MainWindow::newWindow()
{
    dApp->newWindow();
}

void MainWindow::setTitle(int id)
{
    Q_UNUSED(id);

    tab *tabwidget = (tab*)tabs->currentWidget();
    QString title;
    title = tabwidget->webView->title();
    setWindowTitle(title);
}

void MainWindow::tabName(QWidget* id, QString title)
{    
    if(title.isNull()){ tab *tabwidget = (tab*)id; title = tabwidget->webView->url().toString(); }
    tabs->setTabText(tabs->indexOf(id), title);
}

void MainWindow::tabIcon(QWidget *id, QIcon icon)
{
    tabs->setTabIcon(tabs->indexOf(id), icon);
}

void MainWindow::viewSource()//Pobiera kod zrodlowy
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    QNetworkAccessManager* accessManager = tabwidget->webView->page()->networkAccessManager();
    QNetworkRequest request(tabwidget->webView->url());
    QNetworkReply* reply = accessManager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(slotSourceDownloaded()));
}

void MainWindow::slotSourceDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));
    QTextEdit* textEdit = new QTextEdit(NULL);
    textEdit->setAttribute(Qt::WA_DeleteOnClose);
    textEdit->show();
    textEdit->setPlainText(reply->readAll());
    reply->deleteLater();
}

void MainWindow::highlightAllLinks()
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    QString code = "$('a').each( function () { $(this).css('background-color', 'yellow') } )";
    tabwidget->webView->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::removeObjectElements()
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    QString code = "$('object').remove()";
    tabwidget->webView->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::removeEmbeddedElements()
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    QString code = "$('embed').remove()";
    tabwidget->webView->page()->mainFrame()->evaluateJavaScript(code);
}

void MainWindow::openPreferences()
{
    ConfigDialog config;
    config.exec();
}

void MainWindow::exitWindow()
{
    dApp->removeWindow(this);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    exitWindow();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    tabs->updateSize();
}

void MainWindow::showAbout()
{
    QDialog *about = new QDialog(0);
    about->setWindowTitle(tr("About Dragon"));

    QHBoxLayout *mainL = new QHBoxLayout();
    QVBoxLayout *leftL = new QVBoxLayout();
    QVBoxLayout *rightL = new QVBoxLayout();

    QLabel *dragonVersion = new QLabel(tr("Dragon version:\n") + ConfigManager::DragonVersion());
    leftL->addWidget(dragonVersion);

    QLabel *builtDate = new QLabel(tr("Built date:\n") + QString::fromLocal8Bit(BUILDDATE) + " " + QString::fromLocal8Bit(BUILDTIME));
    leftL->addWidget(builtDate);

    QLabel *webkitVersion = new QLabel(tr("Webkit version:\n") + qWebKitVersion());
    leftL->addWidget(webkitVersion);

    QLabel *qtVersion = new QLabel(tr("Qt Libraries version:\n") + qVersion());
    leftL->addWidget(qtVersion);

    QPushButton *ok = new QPushButton("OK");
    leftL->addWidget(ok);
    connect(ok, SIGNAL(clicked()), about, SLOT(close()));

    QTextEdit *authors = new QTextEdit();
    authors->setReadOnly(true);
    authors->append("<center><font size=4><b>Dragon Web Browser</b></font><center>");
    authors->append("<b>Main Developer</b><br/>Rafał Niewiński");
    authors->append("");
    authors->append("<b>Crystal Dragon Cloud Server</b><br/>Jakub Czarniecki");
    rightL->addWidget(authors);

    mainL->addLayout(leftL);
    mainL->addLayout(rightL);
    about->setLayout(mainL);

    about->exec();
}

void MainWindow::showDownloadManager()
{
    dApp->getDownloadManager()->show();
}

void MainWindow::showLibraryHistory()
{
    Library *lib = new Library(2);
    lib->show();
}

void MainWindow::printRequest()
{
    tab *page = (tab*)tabs->currentWidget();
    page->printPage(page->webView->page()->currentFrame());
}

bool MainWindow::saveSession()
{
    if(dApp->getConfigManager()->saveSessionData(tabs->generateAllOpenTabUrls()))
        return true;
    else
        return false;
}

bool MainWindow::restoreSession()
{
    QList<QString> *urls = dApp->getConfigManager()->restoreSessionData();

    for(int i=0; i < urls->count(); i++)
    {
        createTabWithUrl(urls->at(i));
    }

    return true;
}

void MainWindow::cloudStatusChanged(CloudManager::CloudState state)
{

}

void MainWindow::cloudActionCalled()
{
    CloudDialog *dialog = new CloudDialog();
    dialog->exec();
}

void MainWindow::resetZoom()
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    tabwidget->webView->setZoomFactor(1.00);
}

void MainWindow::zoomIn()
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    tabwidget->webView->setZoomFactor(tabwidget->webView->zoomFactor() + 0.10);
}

void MainWindow::zoomOut()
{
    tab *tabwidget = (tab*)tabs->currentWidget();
    tabwidget->webView->setZoomFactor(tabwidget->webView->zoomFactor() - 0.10);
}
