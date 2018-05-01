#include "mainwindow.h"
#include "welcome.h"
#include "rolldice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(true);

    welcome wel;
    rollDice rol;
    MainWindow w;
    if(wel.exec() == QDialog::Accepted){
        if(rol.exec() == QDialog::Accepted){
            w.setFirstPlayer(rol.getFirst());
            w.startTimer();
            w.show();
            return a.exec();
        }

    }
    else if(wel.exec() == QDialog::Rejected){
        a.exit();
    }

    else return 0;
}
