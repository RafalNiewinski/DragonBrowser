#include "downloadslot.h"
#include "Application/dragonbrowser.h"

DownloadSlot::DownloadSlot(QUrl url)
{
    fileUrl = url;
    status = IDLE;

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    fileName = new QLabel("");
    mainLayout->addWidget(fileName);

    progressBar = new QProgressBar();
    mainLayout->addWidget(progressBar);

    downLayout = new QHBoxLayout();
    mainLayout->addLayout(downLayout);

    speedLabel = new QLabel("Speed: -");
    downLayout->addWidget(speedLabel);

    sizeLabel = new QLabel("0 %");
    downLayout->addWidget(sizeLabel);

    actionButton = new QPushButton(tr("Stop"));
    downLayout->addWidget(actionButton);
    connect(actionButton, SIGNAL(clicked()), this, SLOT(buttonAction()));
}

DownloadSlot::~DownloadSlot()
{
    disconnect(actionButton, SIGNAL(clicked()));
    disconnect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)));
    disconnect(currentDownload, SIGNAL(finished()));
    disconnect(currentDownload, SIGNAL(readyRead()));

    delete fileName;
    delete progressBar;
    delete speedLabel;
    delete sizeLabel;
    delete actionButton;
    delete downLayout;
    delete mainLayout;
    delete currentDownload;
}

bool DownloadSlot::start()
{
    if(!prepareFile())
    {
        status = ERR;
        return false;
    }
    else if (!startDownload())
    {
        status = ERR;
        return false;
    }

    return true;
}

bool DownloadSlot::prepareFile()
{
    QString name = QFileInfo(fileUrl.path()).fileName();
    if (name.isEmpty()) name = "download";

    if(dApp->getConfigManager()->getOption("StaticSavePath").toBool() == true && !dApp->getConfigManager()->getOption("SavePath").toString().isEmpty() && QDir(dApp->getConfigManager()->getOption("SavePath").toString()).exists())
    {
        if (QFile::exists(dApp->getConfigManager()->getOption("SavePath").toString() + "/" + name))
        {
            int i = 0;
            name += '.';
            while (QFile::exists(name + QString::number(i))) ++i;

            name += QString::number(i);
        }

        output.setFileName(dApp->getConfigManager()->getOption("SavePath").toString() + "/" + name);
    }
    else
    {
        QString savePath = dApp->getConfigManager()->getOption("LastSavePath").toString();

        if(!savePath.isEmpty() && QDir(savePath).exists())
            output.setFileName(QFileDialog::getSaveFileName(0, tr("Save file"), savePath + "/" + name));
        else
            output.setFileName(QFileDialog::getSaveFileName(0, tr("Save file"), QDir::homePath() + "/" + name));

        if(output.fileName().isEmpty()) return false;

    }

    fileName->setText(QFileInfo(output.fileName()).fileName());

    if (!output.open(QIODevice::WriteOnly)) return false;

    dApp->getConfigManager()->setOption("LastSavePath", QFileInfo(output.fileName()).dir().absolutePath());

    return true;
}

bool DownloadSlot::startDownload()
{
    QNetworkRequest request(fileUrl);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(progressUpdate(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()), this, SLOT(downloadEnded()));
    connect(currentDownload, SIGNAL(readyRead()), this, SLOT(readyRead()));

    downloadTime.start();

    status = DOWNLOADING;
    return true;
}

bool DownloadSlot::stopDownload()
{
    currentDownload->abort();
    progressBar->hide();
    output.close();

    status = ABORTED;
    speedLabel->setText(tr("<b>Aborted</b>"));
    buttonAction();
    return true;
}

bool DownloadSlot::pauseDownlad()
{
    return false;
}

void DownloadSlot::downloadEnded()
{
    progressBar->hide();
    output.close();

    speedLabel->setText(tr("<b>Downloaded</b>"));
    sizeLabel->setVisible(false);

    if(currentDownload->error())
    {
        //download ERROR
        status = ERR;
    }
    else status = DOWNLOADED;
    buttonAction();
}

void DownloadSlot::progressUpdate(qint64 bytesReceived, qint64 bytesTotal)
{
    progressBar->setMaximum(bytesTotal);
    progressBar->setValue(bytesReceived);

    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if(speed < 1024) unit = "bytes/sec";
    else if(speed < 1024*1024)
    {
        speed /= 1024;
        unit = "kB/s";
    }
    else
    {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    speedLabel->setText(QString::fromLatin1("%1 %2").arg(speed, 3, 'f', 1).arg(unit));

    if(bytesTotal < 1024) sizeLabel->setText(QString::fromLatin1("%1 bytes / %2 bytes").arg(bytesReceived).arg(bytesTotal));
    else if(bytesTotal < 1024*1024) sizeLabel->setText(QString::fromLatin1("%1 kB / %2 kB").arg(bytesReceived / 1024).arg(bytesTotal / 1024));
    else sizeLabel->setText(QString::fromLatin1("%1 MB / %2 MB").arg(bytesReceived / (1024*1024)).arg(bytesTotal / (1024*1024)));

    progressBar->update();
}

void DownloadSlot::readyRead()
{
    output.write(currentDownload->readAll());
}

void DownloadSlot::buttonAction()
{
    if(status == DOWNLOADING) stopDownload();
    else if(status == DOWNLOADED) actionButton->hide();
    else if(status == ERR) actionButton->hide();
    else if(status == ABORTED) actionButton->hide();
}
