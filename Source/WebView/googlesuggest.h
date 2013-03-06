#ifndef GOOGLESUGGEST_H
#define GOOGLESUGGEST_H

#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QtWidgets>
#else
        #include <QtGui>
#endif

#include <QtNetwork>
#include <QObject>

class GoogleSuggest : public QObject
{
    Q_OBJECT

public:
    GoogleSuggest(QLineEdit *parent = 0);

    bool eventFilter(QObject *obj, QEvent *ev);
    void showCompletion(const QStringList &choices, const QStringList &hits);

public slots:

    void doneCompletion();
    void preventSuggest();
    void autoSuggest();
    void handleNetworkData(QNetworkReply *networkReply);

private:
    QLineEdit *editor;
    QTreeWidget *popup;
    QTimer *timer;
    QNetworkAccessManager networkManager;
    
};

#endif // GOOGLESUGGEST_H
