#include "downloadmanager.h"

DownloadManager::DownloadManager(QWidget *parent) : QMainWindow(parent)
{
    manager = new QNetworkAccessManager();

    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

void DownloadManager::startDownload(QUrl url)
{
    DownloadSlot *download = new DownloadSlot(url);
    mainLayout->addWidget(download);
    downloads.append(download);
    download->start();

    if(!this->isVisible()) this->show();
}
