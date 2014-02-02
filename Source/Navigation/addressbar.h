#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QStyleOptionFrameV2>
#include <QPainter>
#include <QLinearGradient>

class AddressBar : public QLineEdit
{
public:
    AddressBar();

    virtual void paintEvent(QPaintEvent *);
    void setProgress(int percent);

protected:
    void initStyleOption(QStyleOptionFrameV2 *option) const;
    QLinearGradient generateGradient(const QColor &color) const;

private:
    int progress;
};

#endif // MYLINEEDIT_H
