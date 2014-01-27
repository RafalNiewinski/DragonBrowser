#ifndef CLOUDDIALOG_H
#define CLOUDDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

class CloudDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CloudDialog(QWidget *parent = 0);
    
private:

    void prepareLoginView();

    QVBoxLayout *formLayout;
    QHBoxLayout *loginLayout;
    QHBoxLayout *passwordLayout;
    QLabel *crystalLogo;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *signInButton;
    
};

#endif // CLOUDDIALOG_H
