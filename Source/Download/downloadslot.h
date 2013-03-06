#ifndef DOWNLOADSLOT_H
#define DOWNLOADSLOT_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QtWidgets>
#else
        #include <QtGui>
#endif

#include <QtNetwork>

class DownloadSlot : public QWidget
{
    Q_OBJECT
public:
    DownloadSlot(QUrl url);

    QUrl fileUrl;
    QVBoxLayout *mainLayout;
    QLabel *fileName;
    QProgressBar *progressBar;
    QHBoxLayout *downLayout;
    QLabel *speedLabel;
    QLabel *sizeLabel;
    QPushButton *actionButton;


    QNetworkAccessManager manager;
    QNetworkReply *currentDownload;
    QFile output;
    QTime downloadTime;

    enum state
    {
        DOWNLOADED,
        PAUSE,
        IDLE,
        DOWNLOADING,
        ABORTED,
        ERROR
    };

    state status;

public slots:
    void start();

    bool prepareFile();
    bool startDownload();
    bool stopDownload();
    bool pauseDownlad();
    void downloadEnded();
    void buttonAction();

    void progressUpdate(qint64,qint64);
    void readyRead();

};

#endif // DOWNLOADSLOT_H
