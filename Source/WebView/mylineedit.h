#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : QLineEdit
{
public:
    MyLineEdit();

    virtual void paintEvent(QPaintEvent *);
};

#endif // MYLINEEDIT_H
