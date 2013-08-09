#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QtGui>

class BasicPage : public QWidget
{
public:
    BasicPage(QWidget *parent = 0);

private slots:
    void startComboChanged(int i);
    void homeUrlChanged();

private:
    QComboBox *startCombo;
    QLineEdit *startPageEdit;
};

class QueryPage : public QWidget
{
public:
    QueryPage(QWidget *parent = 0);
};

class UpdatePage : public QWidget
{
public:
    UpdatePage(QWidget *parent = 0);
};

#endif // PAGES_H
