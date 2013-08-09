#include "clouddialog.h"
#include "Application/dragonbrowser.h"

CloudDialog::CloudDialog(QWidget *parent) :
    QDialog(parent)
{
    setMinimumSize(300, 400);

    if(dApp->getCloudManager()->getCloudState() == CloudManager::NONE)
    {
        prepareLoginView();
    }
}

void CloudDialog::prepareLoginView()
{
    formLayout = new QVBoxLayout();
    loginLayout = new QHBoxLayout();
    passwordLayout = new QHBoxLayout();

    QImage cry(qApp->applicationDirPath() + "/Content/ICONS/crystal.png");
    crystalLogo = new QLabel();
    crystalLogo->setPixmap(QPixmap::fromImage(cry));

    loginLabel = new QLabel(tr("Login:"));
    loginEdit = new QLineEdit();
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);

    passwordLabel = new QLabel(tr("Password:"));
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    signInButton = new QPushButton(tr("Sign in"));

    formLayout->addWidget(crystalLogo);
    formLayout->addLayout(loginLayout);
    formLayout->addLayout(passwordLayout);
    formLayout->addWidget(signInButton);

    //loginWidget->setLayout(formLayout);
    setLayout(formLayout);
}
