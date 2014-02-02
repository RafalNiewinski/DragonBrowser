#include "addresscompleterdelegate.h"

#include <QPainter>
#include <QApplication>
#include <QMouseEvent>

AddressCompleterDelegate::AddressCompleterDelegate(QListView *v) : QStyledItemDelegate(v)
{
    view = v;

    rowHeight = 0;
    padding = 0;
}

void AddressCompleterDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);

    const QWidget* w = opt.widget;
    const QStyle* style = w ? w->style() : QApplication::style();

    const int height = opt.rect.height();
    const int center = height / 2 + opt.rect.top();

    //Title font
    QFont titleFont = opt.font;
    titleFont.setPointSize(titleFont.pointSize() + 1);

    const QFontMetrics titleMetrics(titleFont);

    int leftPosition = padding * 2;
    int rightPosition = opt.rect.right() - padding;

    opt.state &= ~QStyle::State_MouseOver;

    if(view->currentIndex() == index)
    {
        opt.state |= QStyle::State_Selected;
    }
    else
    {
        opt.state &= ~QStyle::State_Selected;
    }

#ifdef Q_OS__WIN
    const QPalette::ColorRole colorRole = QPalette::Text;
    const QPalette::ColorRole colorLinkRole = QPalette::Link;
#else
    const QPalette::ColorRole colorRole = opt.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text;
    const QPalette::ColorRole colorLinkRole = opt.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Link;
#endif

    //Background
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, w);

    //TODO: ICON

    const QString searchText = index.data(Qt::UserRole+4).toString();

    //Title
    const int leftTitleEdge = leftPosition + 2;
    const int rightTitleEdge = rightPosition - padding;
    QRect titleRect(leftTitleEdge, opt.rect.top() + padding, rightTitleEdge - leftTitleEdge, titleMetrics.height());
    QString title(titleMetrics.elidedText(index.data(Qt::UserRole+2).toString(), Qt::ElideRight, titleRect.width()));
    painter->setFont(titleFont);

    drawHighlightedTextLine(titleRect, title, searchText, painter, style, opt, colorRole);

    //Link
    const int infoYPos = titleRect.bottom() + opt.fontMetrics.leading() + 2;
    QRect linkRect(titleRect.x(), infoYPos, titleRect.width(), opt.fontMetrics.height());
    const QByteArray linkArray = index.data(Qt::DisplayRole).toByteArray();
    QString link;
    if(!linkArray.startsWith("data") && !linkArray.startsWith("javascript"))
    {
        link = QString::fromUtf8(QByteArray::fromPercentEncoding(linkArray)).left(500);
    }
    else
    {
        link = QString::fromLatin1(linkArray.left(500));
    }

    link = opt.fontMetrics.elidedText(link, Qt::ElideRight, linkRect.width());
    painter->setFont(opt.font);

    drawHighlightedTextLine(linkRect, link, searchText, painter, style, opt, colorLinkRole);

    //Bottom line on non highlited
    if(!(opt.state & QStyle::State_Selected))
    {
        QRect lineRect(opt.rect.left(), opt.rect.bottom(), opt.rect.width(), 1);
        painter->fillRect(lineRect, opt.palette.color(QPalette::AlternateBase));
    }
}

QSize AddressCompleterDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!rowHeight)
    {
        QStyleOptionViewItemV4 opt(option);
        initStyleOption(&opt, index);

        const QWidget* w = opt.widget;
        QStyle* style = w ? w->style() : QApplication::style();
        int p = style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0) + 1;

        QFont titleFont = opt.font;
        titleFont.setPointSize(titleFont.pointSize() + 1);

        padding = p > 3 ? padding : 3;

        QFontMetrics titleMetrics(titleFont);

        rowHeight = 2 * padding + opt.fontMetrics.leading() + opt.fontMetrics.height() + titleMetrics.height() + 2;
    }

    return QSize(200, rowHeight);
}

static bool isBigger(const QString &s1, const QString &s2)
{
    return s1.size() > s2.size();
}

void AddressCompleterDelegate::drawHighlightedTextLine(const QRect &rect, const QString &text, const QString &searchText,
        QPainter* painter, const QStyle* style, const QStyleOptionViewItemV4 &option,
        const QPalette::ColorRole &role) const
{
    QList<int> delimiters;
    QStringList searchStrings = searchText.split(QLatin1Char(' '), QString::SkipEmptyParts);

    // Look for longer parts first
    qSort(searchStrings.begin(), searchStrings.end(), isBigger);

    foreach (const QString &string, searchStrings) {
        int delimiter = text.indexOf(string, 0, Qt::CaseInsensitive);

        while (delimiter != -1) {
            int start = delimiter;
            int end = delimiter + string.length();

            bool alreadyContains = false;
            for (int i = 0; i < delimiters.count(); ++i) {
                int dStart = delimiters.at(i);
                int dEnd = delimiters.at(++i);

                if (dStart <= start && dEnd >= end) {
                    alreadyContains = true;
                    break;
                }
            }

            if (!alreadyContains) {
                delimiters.append(start);
                delimiters.append(end);
            }

            delimiter = text.indexOf(string, end, Qt::CaseInsensitive);
        }
    }

    // We need to sort delimiters to properly paint all parts that user typed
    qSort(delimiters);

    // If we don't find any match, just paint it without any highlight
    if (delimiters.isEmpty() || delimiters.count() % 2) {
        drawTextLine(rect, text, painter, style, option, role);
        return;
    }

    QFont normalFont = painter->font();
    QFont boldFont = normalFont;
    boldFont.setBold(true);

    QFontMetrics normalMetrics(normalFont);
    QFontMetrics boldMetrics(boldFont);

    int lastEndPos = 0;
    int lastRectPos = rect.left();

    while (!delimiters.isEmpty()) {
        int start = delimiters.takeFirst();
        int end = delimiters.takeFirst();

        const QString normalPart = text.mid(lastEndPos, start - lastEndPos);
        const QString boldPart = text.mid(start, end - start);

        lastEndPos = end;

        if (!normalPart.isEmpty()) {
            int width = normalMetrics.width(normalPart);
            QRect nRect = adjustRect(rect, QRect(lastRectPos, rect.top(), width, rect.height()));

            if (nRect.width() > 0) {
                if (text.isRightToLeft()) {
                    nRect = style->visualRect(Qt::RightToLeft, rect, nRect);
                }
                painter->setFont(normalFont);
                drawTextLine(nRect, normalPart, painter, style, option, role);

                lastRectPos += nRect.width();
            }
        }

        if (!boldPart.isEmpty()) {
            int width = boldMetrics.width(boldPart);
            QRect bRect = adjustRect(rect, QRect(lastRectPos, rect.top(), width, rect.height()));

            if (bRect.width() > 0) {
                if (text.isRightToLeft()) {
                    bRect = style->visualRect(Qt::RightToLeft, rect, bRect);
                }
                painter->setFont(boldFont);
                drawTextLine(bRect, boldPart, painter, style, option, role);

                // Paint manually line under text instead of using QFont::underline
                QRect underlineRect(bRect.left(), bRect.top() + boldMetrics.ascent() + 1,
                                    bRect.width(), boldFont.pointSize() > 8 ? 2 : 1);

                painter->fillRect(underlineRect, option.palette.color(role));

                lastRectPos += bRect.width();
            }
        }

        if (delimiters.isEmpty() && lastEndPos != text.size()) {
            const QString lastText = text.mid(lastEndPos);

            int width = normalMetrics.width(lastText);
            QRect nRect = adjustRect(rect, QRect(lastRectPos, rect.top(), width, rect.height()));
            if (text.isRightToLeft()) {
                nRect = style->visualRect(Qt::RightToLeft, rect, nRect);
            }
            painter->setFont(normalFont);
            drawTextLine(nRect, lastText, painter, style, option, role);
        }
    }
}

void AddressCompleterDelegate::drawTextLine(const QRect &rect, QString text, QPainter* painter,
        const QStyle* style, const QStyleOptionViewItemV4 &option,
        const QPalette::ColorRole &role) const
{
    if (rect.width() > 0) {
        const Qt::LayoutDirection direction = option.widget ? option.widget->layoutDirection() : QApplication::layoutDirection();
        Qt::LayoutDirection textDirection = text.isRightToLeft() ? Qt::RightToLeft : Qt::LeftToRight;
        Qt::Alignment alignment = textDirection == direction ? Qt::AlignLeft : Qt::AlignRight;

        // Insert unicode control characters: prepend RLE or LRE and append (RLM or LRM)+PDF
        text.isRightToLeft() ? text.prepend(QChar(0x202B)).append(0x200F) : text.prepend(QChar(0x202A)).append(0x200E);
        text.append(QChar(0x202C));

        style->drawItemText(painter, rect, Qt::TextSingleLine | alignment, option.palette, true, text, role);
    }
}

QRect AddressCompleterDelegate::adjustRect(const QRect &original, const QRect &created) const
{
    if (created.left() + created.width() >= original.right()) {
        QRect nRect = created;
        nRect.setWidth(original.right() - created.left());

        return nRect;
    }

    return created;
}
