#include "welcome.h"
#include "ui_welcome.h"
#include "rolldice.h"
#include "mainwindow.h"

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    connect(ui->begin, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->close, SIGNAL(clicked()), this, SLOT(close()));
}

welcome::~welcome()
{
    delete ui;
}

/*void welcome::accept()
{
    rollDice roll;
    if(roll.exec() == QDialog::Accepted){
        QDialog::accept();
    }
}*/
