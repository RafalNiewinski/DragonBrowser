#include "authdialog.h"

AuthDialog::AuthDialog()
{
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    userLayout = new QHBoxLayout();
    userLabel = new QLabel(tr("Username:"));
    userLayout->addWidget(userLabel);
    userLine = new QLineEdit();
    userLayout->addWidget(userLine);
    mainLayout->addLayout(userLayout);

    passLayout = new QHBoxLayout();
    passLabel = new QLabel(tr("Password:"));
    passLayout->addWidget(passLabel);
    passLine = new QLineEdit();
    //passLine->setInputMask("*");
    passLayout->addWidget(passLine);
    mainLayout->addLayout(passLayout);

    ok = new QPushButton(tr("OK"));
    connect(ok, SIGNAL(clicked()), this, SLOT(confirm()));
    cancel = new QPushButton(tr("Cancel"));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    mainLayout->addWidget(ok);
    mainLayout->addWidget(cancel);
}

void AuthDialog::confirm()
{
    emit authConfirm(userLine->text(), passLine->text());
    this->close();
}
