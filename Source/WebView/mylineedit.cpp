#include "mylineedit.h"

MyLineEdit::MyLineEdit()
{
    QLineEdit();
    this->setMinimumHeight(20);
}

void MyLineEdit::initStyleOption(QStyleOptionFrameV2 *option) const
{
    option->initFrom(this);
    option->rect = contentsRect();
    option->lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, option, this);
    option->midLineWidth = 0;
    option->state |= QStyle::State_Sunken;

    option->features = QStyleOptionFrameV2::None;
}

QLinearGradient MyLineEdit::generateGradient(const QColor &color) const
{
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor::fromRgb(255, 255, 255));
    gradient.setColorAt(0.15, color.lighter(120));
    gradient.setColorAt(0.5, color);
    gradient.setColorAt(0.85, color.lighter(120));
    gradient.setColorAt(1, QColor::fromRgb(255, 255, 255));
    return gradient;
}

void MyLineEdit::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    QStyleOptionFrameV2 panel;
    initStyleOption(&panel);
    style()->drawPrimitive(QStyle::PE_PanelLineEdit, &panel, &p, this);

    if(hasFocus() || progress == 100) QLineEdit::paintEvent(event);

    QPainter painter(this);
    QStyleOptionFrameV2 lenap;
    initStyleOption(&lenap);
    QRect backgroundRect = style()->subElementRect(QStyle::SE_LineEditContents, &lenap, this);

    if(!hasFocus() && progress < 100)
    {
        QColor loadingColor = QColor(116, 192, 250);
        painter.setBrush(generateGradient(loadingColor));
        painter.setPen(Qt::transparent);
        int mid = backgroundRect.width() / 100 * progress;
        QRect progressRect(backgroundRect.x(), backgroundRect.y(), mid, backgroundRect.height());
        painter.drawRect(progressRect);

        painter.setPen(Qt::SolidLine);
        painter.drawText(backgroundRect,Qt::AlignLeft|Qt::AlignVCenter, " " + this->text());
    }
}

void MyLineEdit::setProgress(int percent)
{
    progress = percent;
}
