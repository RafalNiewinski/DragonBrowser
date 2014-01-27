#include <QtGlobal>
#if QT_VERSION >= 0x050000
        #include <QtWidgets/QtWidgets>
#else
        #include <QtGui>
#endif

#include "pages.h"
#include "Application/dragonbrowser.h"

BasicPage::BasicPage(QWidget *parent) : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Basics"));

    QLabel *startLabel = new QLabel(tr("By starting:"));
    startCombo = new QComboBox;
    connect(startCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(startComboChanged(int)));
    startCombo->addItem(tr("Run the startup screen"));
    startCombo->addItem(tr("Start your homepage"));
    startCombo->addItem(tr("Restore last open tabs"));
    //if(dApp->getConfigManager()->startAction == StartupScreen) startCombo->setCurrentIndex(0);
    //else if(dApp->getConfigManager()->startAction == HomePage) startCombo->setCurrentIndex(1);
    //else startCombo->setCurrentIndex(2);
    QHBoxLayout *startOptionLayout = new QHBoxLayout;
    startOptionLayout->addWidget(startLabel);
    startOptionLayout->addWidget(startCombo);

    QLabel *startPageLabel = new QLabel(tr("Start page:"));
    startPageEdit = new QLineEdit(dApp->getConfigManager()->homeAddress);
    connect(startPageEdit, SIGNAL(editingFinished()), this, SLOT(homeUrlChanged()));
    QHBoxLayout *startPageLayout = new QHBoxLayout;
    startPageLayout->addWidget(startPageLabel);
    startPageLayout->addWidget(startPageEdit);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(startOptionLayout);
    configLayout->addLayout(startPageLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void BasicPage::startComboChanged(int i)
{
    //if(i == 0) dApp->getConfigManager()->startAction = StartupScreen;
    //else if(i == 1) dApp->getConfigManager()->startAction = HomePage;
    //else dApp->getConfigManager()->startAction = RestorePages;
}

void BasicPage::homeUrlChanged()
{
    dApp->getConfigManager()->homeAddress = startPageEdit->text();
}

UpdatePage::UpdatePage(QWidget *parent) : QWidget(parent)
{
}

QueryPage::QueryPage(QWidget *parent) : QWidget(parent)
{
}
