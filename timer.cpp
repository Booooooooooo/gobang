#include "timer.h"

Timer::Timer()
{
    QTimer *countDown = new QTimer(this);
    connect(countDown, SIGNAL(timeout()), this, SLOT(countDown()));
    countDown->start(30000);
    time = 1;
    QString s = QString::number(time++, 10);
    ui->lcdNumber->display(s);

    QTimer *clear = new QTimer(this);
    connect(clear, SIGNAL(timeout()), this, SLOT(updateLabel()));
    clear->start(31000);

    QTimer *count = new QTimer(this);
    connect(count, SIGNAL(timeout()), this, SLOT(countTime()));
    count->start(1000);
}

Timer::~Timer()
{

}

