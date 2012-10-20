#include "mainwindow.h"
#include <string>
#include <iostream>
#include "tab.h"
#include "Config/configdialog.h"

MainWindow::MainWindow()
{
    QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));

    setWindowTitle("Dragon Web Browser Alpha");
    //setWindowIcon(QIcon("/path/window_icon.png"));

    QApplication::setStyle(new QPlastiqueStyle);

    createFileActions();
    createMenus();
    createUi();
    createConnects();

    setMinimumSize(160, 160);
    this->showMaximized();
}

void MainWindow::createFileActions()
{
    newTabAction = new QAction(tr("New tab"), this);
    newTabAction->setShortcut(Qt::CTRL + Qt::Key_T);
    connect(newTabAction, SIGNAL(triggered()), this, SLOT(createTab()));

    closeTabAction = new QAction(tr("Close tab"), this);
    closeTabAction->setShortcut(Qt::CTRL + Qt::Key_W);
    connect(closeTabAction, SIGNAL(triggered()), this, SLOT(deleteCurrentTab()));

    newWindowAction = new QAction(tr("New window"), this);
    newWindowAction->setShortcut(Qt::CTRL + Qt::Key_N);
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    saveAsImageAction = new QAction(tr("Save screenshoot of page"), this);
    //saveAsImageAction->setShortcut();

    printPageAction = new QAction(tr("Print page"), this);
    printPageAction->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(printPageAction, SIGNAL(triggered()), this, SLOT(printRequest()));

    quitAction = new QAction(tr("Quit"), this);
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(exitApplication()));

    viewSourceAction = new QAction("Source code", this);
    connect(viewSourceAction, SIGNAL(triggered()), SLOT(viewSource()));

    downloadManagerAction = new QAction(tr("Download manager"), this);
    connect(downloadManagerAction, SIGNAL(triggered()), this, SLOT(showDownloadManager()));

    preferencesAction = new QAction(tr("Preferences"), this);
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(openPreferences()));

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
    viewMenu->addAction(tr("Highlight all links"), this, SLOT(highlightAllLinks()));
    viewMenu->addAction(tr("Remove all object elements"), this, SLOT(removeObjectElements()));
    viewMenu->addAction(tr("Remove all embedded elements"), this, SLOT(removeEmbeddedElements()));

    toolsMenu = new QMenu(tr("Tools"), this);
    menuBar()->addMenu(toolsMenu);
    toolsMenu->addAction(downloadManagerAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(preferencesAction);


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

    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);
    tabs->setDocumentMode(true);
    tabs->setUsesScrollButtons(false);
    tabs->setElideMode(Qt::ElideRight);
    tabs->setCornerWidget(addTabButton, Qt::TopRightCorner);

    layout->addWidget(tabs);

    checkSystemDir();

    cookieJar = new MyCookieJar();
    nManager = new QNetworkAccessManager();
    nManager->setCookieJar(cookieJar);

    configurationLoader = new ConfigManager();
    cookieJar->loadAllCookies();

    downloadManager = new DownloadManager();

    createTab();
}

void MainWindow::createConnects()
{
    connect(saveAsImageAction, SIGNAL(triggered()), this, SLOT(saveAsImage()));
    connect(addTabButton, SIGNAL(clicked()), this, SLOT(createTab()));
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteTab(int)));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(setTitle(int)));
    connect(nManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authorizationRequest(QNetworkReply*,QAuthenticator*)));
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

void MainWindow::createTab()
{
    tab* page;
    page = new tab(0, configurationLoader);
    tabs->addTab(page, "Blank tab");

    page->webView->page()->setNetworkAccessManager(nManager);

    connect(page, SIGNAL(chTitleSig(QWidget*,QString)), this, SLOT(tabName(QWidget*,QString)));
    connect(page, SIGNAL(downloadRequestSig(QUrl)), downloadManager, SLOT(startDownload(QUrl)));
    connect(page, SIGNAL(openNewTab(QUrl)), this, SLOT(createTabWithUrl(QUrl)));
    tabs->setCurrentIndex(tabs->indexOf(page));
}

void MainWindow::createTabWithUrl(QUrl url)
{
    tab* page;
    page = new tab(0, configurationLoader);
    tabs->addTab(page, "Blank tab");

    page->webView->page()->setNetworkAccessManager(nManager);

    connect(page, SIGNAL(chTitleSig(QWidget*,QString)), this, SLOT(tabName(QWidget*,QString)));
    connect(page, SIGNAL(downloadRequestSig(QUrl)), downloadManager, SLOT(startDownload(QUrl)));
    connect(page, SIGNAL(openNewTab(QUrl)), this, SLOT(createTabWithUrl(QUrl)));

    page->webView->setUrl(url);
    tabs->setCurrentIndex(tabs->indexOf(page));
}

void MainWindow::deleteTab(int index)
{
    if(tabs->count() == 0) exitApplication();
    tab *tabwidget = (tab*)tabs->widget(index);
    delete tabwidget;
}

void MainWindow::deleteCurrentTab()
{
    deleteTab(tabs->currentIndex());
}

void MainWindow::newWindow()
{
    //system("./DragonWebBrowser");
}

void MainWindow::setTitle(int id)
{
    Q_UNUSED(id);

    tab *tabwidget = (tab*)tabs->currentWidget();
    QString title;
    title = tabwidget->webView->title();
    setWindowTitle(title);
}

void MainWindow::tabName(QWidget* idw, QString title)
{
    tabs->setTabText(tabs->indexOf(idw), title);
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

void MainWindow::exitApplication()
{
    cookieJar->saveAllCookies();
    QApplication::exit(0);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    cookieJar->saveAllCookies();
    QApplication::exit(0);
}

bool MainWindow::checkSystemDir()
{
    #ifdef Q_OS_LINUX

    QString env = getenv("HOME");

    if(QDir(env + "/.DragonWebBrowser").exists() == true) return true;
    if(QDir().mkdir(env + "/.DragonWebBrowser") != true) return true;
    else return false;

    #endif

    return true;
}

void MainWindow::showAbout()
{
    QDialog *about = new QDialog(0);
    about->setWindowTitle(tr("About Dragon"));

    QHBoxLayout *mainL = new QHBoxLayout();
    QVBoxLayout *leftL = new QVBoxLayout();
    QVBoxLayout *rightL = new QVBoxLayout();

    QLabel *builtDate = new QLabel(tr("Built date:\n") + QString::fromLocal8Bit(BUILDDATE) + " " + QString::fromLocal8Bit(BUILDTIME));
    leftL->addWidget(builtDate);

    QPushButton *ok = new QPushButton("OK");
    leftL->addWidget(ok);
    connect(ok, SIGNAL(clicked()), about, SLOT(close()));

    mainL->addLayout(leftL);
    mainL->addLayout(rightL);
    about->setLayout(mainL);

    about->exec();
}

void MainWindow::showDownloadManager()
{
    downloadManager->show();
}

void MainWindow::authorizationRequest(QNetworkReply *reply, QAuthenticator *auth)
{
    Q_UNUSED(reply);

    authenticator = auth;
    AuthDialog *dialog = new AuthDialog();
    connect(dialog, SIGNAL(authConfirm(QString,QString)), this, SLOT(authorizationConfirm(QString,QString)));
    dialog->exec();
}

void MainWindow::authorizationConfirm(QString user, QString password)
{
    authenticator->setUser(user);
    authenticator->setPassword(password);
}

void MainWindow::printRequest()
{
    tab *page = (tab*)tabs->currentWidget();
    page->printPage(page->webView->page()->currentFrame());
}
