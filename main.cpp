#include "mainwindow.h"
#include "welcome.h"
#include "rolldice.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(true);

    welcome wel;
    rollDice rol;
    MainWindow w;
    int flag = -1;
    if(wel.exec() == QDialog::Accepted){
        //if(rol.exec() == QDialog::Accepted){
        w.restart(wel.firstPlayer, wel.type);
        //qDebug()<<wel.firstPlayer;
        w.show();
            return a.exec();
        //}

    }
    else{
        a.exit();
    }

    return 0;
}
