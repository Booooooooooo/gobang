#include "welcome.h"
#include "ui_welcome.h"
#include "rolldice.h"
#include "mainwindow.h"

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    setWindowTitle(tr("五子棋"));
    connect(ui->begin, SIGNAL(clicked()), this, SLOT(person()));
    connect(ui->close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ai, SIGNAL(clicked()), this, SLOT(computer()));
}

welcome::~welcome()
{
    delete ui;
}

void welcome::person()
{
    rollDice roll;
    type = 0;
    roll.setType(type);
    if(roll.exec() == QDialog::Accepted){
        QDialog::accept();
        firstPlayer = roll.firstPlayer;
    }
    else{
        QDialog::reject();
        close();
    }

}

void welcome::computer()
{
    rollDice roll;
    type = 1;
    roll.setType(type);
    if(roll.exec() == QDialog::Accepted){
        QDialog::accept();
        firstPlayer = roll.firstPlayer;
    }
    else{
        QDialog::reject();
        close();
    }

}
