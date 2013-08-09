#include "historyview.h"

HistoryView::HistoryView()
{
    model = new QStandardItemModel();
    model->insertColumn(0);
    model->insertColumn(1);
    model->insertColumn(2);
    model->insertColumn(3);
    model->setHorizontalHeaderLabels(QStringList()<<tr("Title") <<tr("Counts") <<tr("Last Visit") <<tr("Address"));

    prepareView();
}

void HistoryView::prepareView()
{
    QList<HistoryEntry> entries = HistoryManager::fullHistory();

    for(int i=0; i < entries.size(); i++)
    {
        QList<QStandardItem*> roww;

        roww.append(new QStandardItem(entries.at(i).title));
        roww.append(new QStandardItem(QString::number(entries.at(i).count)));
        roww.append(new QStandardItem(entries.at(i).date.toString()));
        roww.append(new QStandardItem(entries.at(i).url));

        items.append(roww);
        model->appendRow(roww);
    }

    this->setModel(model);
}
