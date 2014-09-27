#include "dragonbrowser.h"

DragonBrowser::DragonBrowser(int &argc, char** argv) : QtSingleApplication(argc, argv)
{

    #if QT_VERSION >= 0x050000
            qApp->setStyle("fusion");
    #else
            QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8")); // QT5 default encoding UTF-8
            QApplication::setStyle(new QPlastiqueStyle); //QT5 do not have trash styles
    #endif

    setApplicationName("Dragon Browser");
    setApplicationVersion(ConfigManager::DragonVersion());
    setOrganizationDomain("dragonbrowser");


    QDesktopServices::setUrlHandler("http", this, "addNewTab");

    connect(this, SIGNAL(messageReceived(QString)), this, SLOT(parameterFromAnotherProcess(QString)));

    cookieJar = new MyCookieJar();
    nManager = new QNetworkAccessManager();
    nManager->setCookieJar(cookieJar);

    configurationLoader = new ConfigManager();
    databaseManager = new DatabaseManager();
    pluginManager = new DragonPluginManager();
    historyManager = new HistoryManager();
    cloudManager = new CloudManager();

    MainWindow* window = new MainWindow();
    mainWindows.prepend(window);
    setActivationWindow(window, true);

    if(ConfigManager::checkSystemDir())
    {
        if(!configurationLoader->loadConfiguration()) QMessageBox::warning(mainWindows.last().data(), ("Configuration Error"), ("Loading your browser settings failed. Loaded default settings."));
        if(!cookieJar->loadAllCookies()) QMessageBox::warning(mainWindows.last().data(), ("Cookies Error"), ("Loading cookies failed. The browser will work without them."));
        if(!databaseManager->openConnection()) QMessageBox::warning(mainWindows.last().data(), ("Database Error"), ("A problem with database is detected: " + databaseManager->getError().text()));
        historyManager->checkDatabase();

        downloadManager = new DownloadManager();

        pluginManager->searchPlugins();

        if(configurationLoader->getOption("StartAction") == "RestoreSession") mainWindows.last().data()->restoreSession();
        else mainWindows.last().data()->createStandardTab();
    }
    else
    {
        configurationLoader->loadDefaults();
        downloadManager = new DownloadManager();
        mainWindows.last().data()->createStandardTab();

        QMessageBox::warning(mainWindows.last().data(), tr("Profile Directory Error"), tr("A problem with creating a user profile directory.\nIf not solved all your data such as configuration can not be saved.\nMake sure that the Dragon has premission to write to the user's home directory."));
    }

    window->show();
    window->showMaximized();

    if(!QString(argv[1]).isEmpty()) mainWindows.last().data()->createTabWithUrl(QUrl(QString(argv[1]))); //Open website in parameter (if exists)
}

QList<MainWindow*> DragonBrowser::getMainWindows()
{
    QList<MainWindow*> list;

    for(int i=0; i < mainWindows.count(); i++)
    {
        if(!mainWindows.at(i)) continue;

        list.append(mainWindows.at(i).data());
    }

    return list;
}

MainWindow* DragonBrowser::newWindow(QUrl url)
{
    MainWindow* window = new MainWindow();
    mainWindows.prepend(window);
    window->createStandardTab();
    window->show();
    window->showMaximized();

    return window;
}

bool DragonBrowser::removeWindow(MainWindow *window)
{
    if(mainWindows.count() == 1) exitApplication();
    bool ok = mainWindows.removeOne(window);
    delete window;
    return ok;
}

void DragonBrowser::parameterFromAnotherProcess(QString parameter)
{
    if(!parameter.isEmpty()) mainWindows.last().data()->createTabWithUrl(QUrl(parameter));
}

void DragonBrowser::exitApplication()
{
    if(ConfigManager::checkSystemDir())
    {
        cookieJar->saveAllCookies();
        mainWindows.last().data()->saveSession();
    }
    else
    {
        QMessageBox::warning(mainWindows.last().data(), "Profile Directory Error", tr("A problem with creating a user profile directory.\nYour personal settings will not be saved until it's fixed.\n\n\nMake sure that the Dragon has permission to write to the user's home directory."));
    }

    this->exit(0);
}

void DragonBrowser::authorizationRequest(QNetworkReply* reply, QAuthenticator* auth)
{
    Q_UNUSED(reply);

    authenticator = auth;
    AuthDialog* dialog = new AuthDialog();
    connect(dialog, SIGNAL(authConfirm(QString,QString)), this, SLOT(authorizationConfirm(QString,QString)));
    dialog->exec();
}

void DragonBrowser::authorizationConfirm(QString user, QString password)
{
    authenticator->setUser(user);
    authenticator->setPassword(password);
}
