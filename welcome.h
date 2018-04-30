#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class welcome;
}

class welcome : public QDialog
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();

private slots:
    //void accept();

private:
    Ui::welcome *ui;

};

#endif // WELCOME_H
