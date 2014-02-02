#ifndef ADDRESSCOMPLETERDELEGATE_H
#define ADDRESSCOMPLETERDELEGATE_H

#include <QStyledItemDelegate>
#include <QListView>

class AddressCompleterDelegate : public QStyledItemDelegate
{
public:
    AddressCompleterDelegate(QListView* v);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void drawHighlightedTextLine(const QRect &rect, const QString &text, const QString &searchText,
                                     QPainter* painter, const QStyle* style, const QStyleOptionViewItemV4 &option,
                                     const QPalette::ColorRole &role) const;

    void drawTextLine(const QRect &rect, QString text, QPainter* painter,
                          const QStyle* style, const QStyleOptionViewItemV4 &option,
                          const QPalette::ColorRole &role) const;

    inline QRect adjustRect(const QRect &original, const QRect &created) const;


    QListView* view;

    mutable int rowHeight;
    mutable int padding;
};

#endif // ADDRESSCOMPLETERDELEGATE_H
