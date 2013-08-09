#include "library.h"

Library::Library(int element)
{
    this->setFixedSize(800, 600);
    move(QApplication::desktop()->screen()->rect().center()-this->rect().center());

    mainWidget = new QWidget();

    fancyTab = new FancyTabWidget();
    layout = new QVBoxLayout();
    layout->addWidget(fancyTab);
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    fancyTab->AddTab(new QWidget(), QIcon("zzz"), tr("Plugins"));
    fancyTab->AddTab(new QWidget(), QIcon("zzz"), tr("Bookmarks"));

    historyWidget = new HistoryWidget();

    fancyTab->AddTab(historyWidget, QIcon("sss"), tr("History"));

    fancyTab->SetMode(FancyTabWidget::Mode_LargeSidebar);

    fancyTab->SetCurrentIndex(element);
}
