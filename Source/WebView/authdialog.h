#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QtGui>

class AuthDialog : public QDialog
{
    Q_OBJECT
public:
    AuthDialog();

    QVBoxLayout *mainLayout;

    QHBoxLayout *userLayout;
    QLabel *userLabel;
    QLineEdit *userLine;

    QHBoxLayout *passLayout;
    QLabel *passLabel;
    QLineEdit *passLine;

    QPushButton *ok;
    QPushButton *cancel;

signals:
    void authConfirm(QString user, QString pass);

private slots:
    void confirm();
};

#endif // AUTHDIALOG_H
