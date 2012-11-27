#include "downloadmanager.h"

DownloadManager::DownloadManager(QWidget *parent) : QMainWindow(parent)
{
    manager = new QNetworkAccessManager();

    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

void DownloadManager::startDownload(QNetworkRequest request)
{
    QNetworkReply *reply = manager->get(request);
    startDownload(reply);
}

void DownloadManager::startDownload(QNetworkReply *reply)
{
    DownloadSlot *download = new DownloadSlot(reply->url());
    mainLayout->addWidget(download);
    downloads.append(download);
    download->start();

    if(!this->isVisible()) this->show();
    if(!this->isActiveWindow()) this->activateWindow();
}

void DownloadManager::startDownload(QUrl url)
{
    QNetworkRequest request(url);
    startDownload(request);
}
