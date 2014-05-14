#include "mywebpage.h"

MyWebPage::MyWebPage(ConfigManager *cm)
{
    QWebPage();
    cfg = cm;
}

MyWebPage::~MyWebPage()
{
}

bool MyWebPage::supportsExtension(Extension extension) const
{
    Q_UNUSED(extension);
    return true;
}

bool MyWebPage::extension(Extension extension, const ExtensionOption *option, ExtensionReturn *output)
{
    if(extension == ChooseMultipleFilesExtension)
    {
        const QWebPage::ChooseMultipleFilesExtensionOption* mfeOption = static_cast<const QWebPage::ChooseMultipleFilesExtensionOption*>(option);
        QWebPage::ChooseMultipleFilesExtensionReturn* mfeReturn = static_cast<QWebPage::ChooseMultipleFilesExtensionReturn*>(output);

        if(!mfeOption || !mfeReturn)
            return QWebPage::extension(extension, option, output);

        mfeReturn->fileNames = QFileDialog::getOpenFileNames(0, tr("Select files to upload"));
        return true;
    }

    const ErrorPageExtensionOption* exOption = static_cast<const QWebPage::ErrorPageExtensionOption*>(option);
    ErrorPageExtensionReturn* exReturn = static_cast<QWebPage::ErrorPageExtensionReturn*>(output);

    if(!exOption || !exReturn) return QWebPage::extension(extension, option, output);

    MyWebPage* erPage = qobject_cast<MyWebPage*>(exOption->frame->page());

    if(!erPage) return QWebPage::extension(extension, option, output);

    QString errorString;
    if(exOption->domain == QWebPage::QtNetwork)
    {
        switch(exOption->error)
        {
        case QNetworkReply::ConnectionRefusedError:
            errorString = tr("Connection refused by server");
            break;
        case QNetworkReply::RemoteHostClosedError:
            errorString = tr("Connection closed by server");
            break;
        case QNetworkReply::HostNotFoundError:
            errorString = tr("Server not found");
            break;
        case QNetworkReply::TimeoutError:
            errorString = tr("Connection timed out");
            break;
        case QNetworkReply::SslHandshakeFailedError:
            errorString = tr("Untrusted connection");
            break;
        case QNetworkReply::TemporaryNetworkFailureError:
            errorString = tr("Temporary network failure");
            break;
        case QNetworkReply::ProxyConnectionRefusedError:
            errorString = tr("Proxy connection refused");
            break;
        case QNetworkReply::ProxyNotFoundError:
            errorString = tr("Proxy not found");
            break;
        case QNetworkReply::ProxyTimeoutError:
            errorString = tr("Proxy connection timed out");
            break;
        case QNetworkReply::ProxyAuthenticationRequiredError:
            errorString = tr("Proxy authentication required");
            break;
        case QNetworkReply::ContentNotFoundError:
            errorString = tr("Content not found");
            break;
        case QNetworkReply::UnknownNetworkError:
            errorString = exOption->errorString.isEmpty() ? tr("Unknown network error") : exOption->errorString;
            break;
        case QNetworkReply::ProtocolUnknownError:
        {
            const QUrl unknownProtocolUrl = (exOption->url.toString() == QLatin1String("?")) ? erPage->mainFrame()->requestedUrl() : exOption->url;
            handleUnknownProtocol(unknownProtocolUrl);
            return false;
        }
        case QNetworkReply::ContentAccessDenied:
            errorString = tr("Access Danied");
            break;
        default:
            return false;
            break;
        }
    }
    else if(exOption->domain == QWebPage::Http)
    {
        //code 200 = OK
        if(exOption->error == 200) return false;
        errorString = tr("Http error... Code: %1").arg(exOption->error);
    }
    else if(exOption->domain == QWebPage::WebKit)
        return false;



    const QUrl &errorUrl = exOption->url;
    exReturn->baseUrl = errorUrl;

    QFile file(qApp->applicationDirPath() + "/Content/HTML/error.html");
    file.open(QFile::ReadOnly);
    QString errorHtml = file.readAll();
    errorHtml.replace(QLatin1String("%TITLE%"), tr("An error has occurred while loading the page."));

    QString head = errorUrl.host().isEmpty() ? tr("Dragon Browser can't load page.") : tr("Dragon Browser can't load page from %1").arg(errorUrl.host());

    errorHtml.replace(QLatin1String("%HEAD%"), errorString);
    errorHtml.replace(QLatin1String("%FROM%"), head);

    errorHtml.replace(QLatin1String("%LI-1%"), tr("Check that the entered URL is correct."));
    errorHtml.replace(QLatin1String("%LI-2%"), tr("Check if your computer is still connected to the Internet."));
    errorHtml.replace(QLatin1String("%LI-3%"), tr("If your other network programs works fine check if your firewall is not blocking Dragon."));

    errorHtml.replace(QLatin1String("%RELOAD%"), tr("Try Again"));

    exReturn->content = QString(errorHtml + "<span id=\"dragon-error-page\"></span>").toUtf8();
    return true;
}

void MyWebPage::handleUnknownProtocol(const QUrl &url)
{
    const QString &protocol = url.scheme();

    QDesktopServices::openUrl(url);
}
