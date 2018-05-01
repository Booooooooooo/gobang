#include "rolldice.h"
#include "ui_rolldice.h"
#include "mainwindow.h"
#include <QPainter>
#include <QSound>
#include <QDebug>

rollDice::rollDice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rollDice)
{
    ui->setupUi(this);
    setWindowTitle(tr("五子棋"));
    rollingFlag = false;
    k = 0;

    bgfile = "../gobang/image/1.jpg";
    bgMovie = new QMovie("../gobang/image/dice.gif");
    diceLabel = new QLabel;
    diceLabel->setGeometry(0,0,100,100);
    diceLabel->setAutoFillBackground(true);
    diceLabel->setFixedSize(300, 300);

    diceLabel->setMovie(bgMovie);
    QPixmap pixmap = QPixmap(bgfile);
    diceLabel->setScaledContents(true);
    diceLabel->setPixmap(pixmap);
    diceLabel->setAlignment(Qt::AlignCenter);
    rollButton = new QPushButton(tr("Roll"));
    layout = new QVBoxLayout;
    layout->addWidget(diceLabel, Qt::AlignCenter);
    layout->addWidget(rollButton);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
    connect(rollButton, SIGNAL(clicked()), this, SLOT(roll()));

    resultLabel = new QLabel(tr("数字大的为先手"));
    resultLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(resultLabel, Qt::AlignCenter);

    beginButton = new QPushButton(tr("开始游戏"));
    beginButton->setVisible(false);
    connect(beginButton, SIGNAL(clicked()), this, SLOT(accept()));
    layout->addWidget(beginButton);
}

void rollDice::setType(int type)
{
    this->type = type;
}

rollDice::~rollDice()
{
    delete ui;
}

int rollDice::getFirst()
{
    return firstPlayer;
}

int rollDice::getType()
{
    return type;
}

void rollDice::roll()
{
    if(!rollingFlag){
        rollingFlag = true;
        rollButton->setText("Stop");
        QSound::play("../gobang/sound/roll.wav");
        diceLabel->setMovie(bgMovie);
        qDebug() << type;
        if(k == 0){
            beginButton->setVisible(false);
            if(type == 0){
                resultLabel->setText(tr("玩家一掷骰子"));
            }
            else{
                resultLabel->setText(tr("玩家掷骰子"));
            }

        }
        else{
            if(type == 0){
                resultLabel->setText(tr("玩家二掷骰子"));
            }
            else{
                resultLabel->setText(tr("电脑掷骰子"));
            }
        }

        bgMovie->start();
        qsrand(QDateTime::currentDateTime().toTime_t());
    }
    else{
        rollingFlag = false;
        rollButton->setText(tr("Roll"));
        diceLabel->setMovie(bgMovie);
        bgMovie->stop();
        //diceLabel->clear();
        int temp = qrand() % 6 + 1;
        //bool isWhite;
        switch(temp){
        case 1: bgfile = "../gobang/image/1.jpg";break;
        case 2: bgfile = "../gobang/image/2.jpg";break;
        case 3: bgfile = "../gobang/image/3.jpg";break;
        case 4: bgfile = "../gobang/image/4.jpg";break;
        case 5: bgfile = "../gobang/image/5.jpg";break;
        case 6: bgfile = "../gobang/image/6.jpg";break;
        }

        if(k == 0){
            k = temp;
        }
        else if(temp > k){
            if(type == 0){
                resultLabel->setText(tr("玩家一为后手，玩家二为先手"));
            }
            else{
                resultLabel->setText(tr("玩家为后手，电脑为先手"));
            }

            firstPlayer = 2;
            beginButton->setVisible(true);
            k = 0;
        }
        else if(temp < k){
            if(type == 0){
                resultLabel->setText(tr("玩家一为先手，玩家二为后手"));
            }
            else{
                resultLabel->setText(tr("玩家为先手，电脑为后手"));
            }

            firstPlayer = 1;
            beginButton->setVisible(true);
            k = 0;
        }
        else{
            resultLabel->setText(tr("平局，请重置"));
            k = 0;
        }

        diceLabel->setPixmap(bgfile);
        //diceLabel->setText("abc");
    }
}
