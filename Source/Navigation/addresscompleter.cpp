#include "addresscompleter.h"

#include <QList>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QApplication>
#include "addresscompleterdelegate.h"

AddressCompleter::AddressCompleter(AddressBar* bar, QObject *parent) : QObject(parent)
{
    addressBar = bar;

    view = new QListView();
    view->setWindowFlags(Qt::Popup);
    view->setUniformItemSizes(true);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setMouseTracking(true);
    view->installEventFilter(this);

    model = new QStandardItemModel();
    view->setModel(model);

    view->setItemDelegate(new AddressCompleterDelegate(view));

    connect(addressBar, SIGNAL(textEdited(QString)), this, SLOT(urlSuggestions(QString)));

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(selected()));
    connect(view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex)));
}

void AddressCompleter::urlSuggestions(QString url)
{
    QList<QStandardItem*> items;

    QSqlQuery query;
    query.exec(QString("SELECT id, title, url, count FROM history WHERE title LIKE '%%1%' OR url LIKE '%%1%' ORDER BY count DESC LIMIT 25").arg(url));

    while(query.next())
    {
        QStandardItem* item = new QStandardItem;

        item->setText(query.value(2).toString());
        item->setData(query.value(0), Qt::UserRole+1);
        item->setData(query.value(1), Qt::UserRole+2);
        item->setData(query.value(3), Qt::UserRole+3);
        item->setData(url, Qt::UserRole+4);

        items.append(item);
    }

    model->clear();
    model->appendColumn(items);

    showSuggestions();
}

void AddressCompleter::showSuggestions()
{
    if(model->rowCount() == 0)
    {
        view->close();
        return;
    }

    QRect viewRect(addressBar->mapToGlobal(QPoint(0, 0)), addressBar->size());
    viewRect.setY(viewRect.bottom());

    view->setFocusProxy(addressBar);
    view->setGeometry(viewRect);

    int h = view->sizeHintForRow(0) * qMin(7, model->rowCount()) + 3;
    view->resize(view->width(), h);

    view->show();
}

void AddressCompleter::selectionChanged(QModelIndex to)
{
    addressBar->setText(to.data().toString());
    addressBar->end(false);
}

void AddressCompleter::selected()
{
    view->hide();
    emit itemChoosed(view->currentIndex().data().toString());
}

bool AddressCompleter::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)
        // Based on QCompleter::eventFilter

        switch (event->type()) {
        case QEvent::KeyPress: {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            QModelIndex curIndex = view->currentIndex();
            if ((keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
                    && view->currentIndex() != curIndex) {
                view->setCurrentIndex(curIndex);
            }

            switch (keyEvent->key()) {
            case Qt::Key_Return:
            case Qt::Key_Enter:
                view->hide();
                break;

            case Qt::Key_End:
            case Qt::Key_Home:
                if (keyEvent->modifiers() & Qt::ControlModifier) {
                    return false;
                }
                break;

            case Qt::Key_Escape:
                view->close();
                return false;

            case Qt::Key_F4:
                if (keyEvent->modifiers() == Qt::AltModifier)  {
                    view->close();
                    return false;
                }
                break;

            case Qt::Key_Tab:
            case Qt::Key_Backtab: {
                Qt::Key k = keyEvent->key() == Qt::Key_Tab ? Qt::Key_Down : Qt::Key_Up;
                QKeyEvent ev(QKeyEvent::KeyPress, k, Qt::NoModifier);
                QApplication::sendEvent(this, &ev);
                return false;
            }

            case Qt::Key_Up:
                if (!curIndex.isValid()) {
                    int rowCount = view->model()->rowCount();
                    QModelIndex lastIndex = view->model()->index(rowCount - 1, 0);
                    view->setCurrentIndex(lastIndex);
                    return true;
                }
                else if (curIndex.row() == 0) {
                    view->setCurrentIndex(QModelIndex());
                    return true;
                }
                return false;

            case Qt::Key_Down:
                if (!curIndex.isValid()) {
                    QModelIndex firstIndex = view->model()->index(0, 0);
                    view->setCurrentIndex(firstIndex);
                    return true;
                }
                else if (curIndex.row() == view->model()->rowCount() - 1) {
                    view->setCurrentIndex(QModelIndex());
                    view->scrollToTop();
                    return true;
                }
                return false;

            case Qt::Key_Delete:
                break;

            case Qt::Key_PageUp:
            case Qt::Key_PageDown:
                return false;

            case Qt::Key_Shift:
                break;
            } // switch (keyEvent->key())

            (static_cast<QObject*>(view->focusProxy()))->event(keyEvent);
            return true;
        }

        case QEvent::MouseButtonPress:
            if (!view->underMouse()) {
                view->close();
                return true;
            }
            break;

        case QEvent::ShortcutOverride:
        case QEvent::InputMethod:
            QApplication::sendEvent(view->focusProxy(), event);
            break;

        default:
            break;
        } // switch (event->type())

        return false;
}
