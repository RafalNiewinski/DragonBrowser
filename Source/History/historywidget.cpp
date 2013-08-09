#include "historywidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout();
    setLayout(layout);

    historyView = new HistoryView();
    layout->addWidget(historyView);


}
