#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcome.h"
#include "rolldice.h"
#include <QPainter>
#include <QToolBar>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QtGlobal>
#include <QCloseEvent>
#include <QMessageBox>
#include <cmath>
#include <QSound>


const int menuSize = 24;//菜单栏宽度
const int boardMargin = 30;//棋盘边缘
const int radius = 15;//棋子半径
const int smallRadius = 4;//圆心点半径
const int markSize = 6;//落子标记边长
const int blockSize = 40;//格子大小
const double posDelta = sqrt(40 * 40 * 2) / 2;//模糊距离
const int displaySize = 50;//显示大小
const int windowHeight = menuSize + boardSize * blockSize + boardMargin * 2 + displaySize;
const int windowWidth = boardSize * blockSize + boardMargin * 2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("五子棋"));
    setIconSize(QSize(menuSize, menuSize));
    this->resize(windowWidth,windowHeight);
    ui->lcdNumber->setParent(this);
    ui->lcdNumber->setStyleSheet("border: 1px solid black; background: white");
    ui->lcdNumber->setGeometry(boardMargin + 5 * blockSize, menuSize  + boardSize * blockSize + boardMargin * 2, windowWidth / 4, displaySize);
    ui->playerLabel->setParent(this);
    ui->playerLabel->setGeometry(boardMargin, menuSize + boardSize * blockSize + boardMargin * 2, windowWidth / 4, displaySize);
    ui->playerLabel->setFont(QFont("Timers", 12, QFont::Bold));
    ui->timeLabel->setParent(this);
    ui->timeLabel->setFont(QFont("Timers", 12, QFont::Bold));
    ui->timeLabel->setGeometry(boardMargin + 10 * blockSize,boardSize * blockSize + boardMargin * 2, windowWidth / 4, displaySize);
    turn = 1;
    initGame();
    down = new QTimer(this);
    connect(down, SIGNAL(timeout()), this, SLOT(countDown()));
    clear = new QTimer(this);
    connect(clear, SIGNAL(timeout()), this, SLOT(updateLabel()));
    count = new QTimer(this);
    connect(count, SIGNAL(timeout()), this, SLOT(countTime()));
}

void MainWindow::setGameType(int type)
{
    this->type = type;
    game->gameType = type;
}

void MainWindow::startTimer()
{
    down->start(30000);
    clear->start(31000);
    count->start(1000);

    time = 30;
    QString s = QString::number(time--, 10);
    ui->lcdNumber->display(s);

}

void MainWindow::countDown()
{
    ui->timeLabel->setText(tr("超时！"));
    time = 30;
    QSound::play("../gobang/sound/timeout.wav");
    //超时随机落子
    while(1)
    {
        qsrand(QDateTime::currentDateTime().toTime_t());
        int row = qrand() % boardSize + 1;
        int col = qrand() % boardSize + 1;
        if(game->gameMap[row][col] == -1){
            game->gameMap[row][col] = turn;
            clickPosRow = row;
            clickPosCol = col;
            turn = !turn;
            if(turn == game->player1.getTurn()){
                ui->playerLabel->setText(tr("玩家一落子"));
            }
            else{
                if(type == 1){
                    //ui->playerLabel->setText(tr("电脑落子"));
                    game->actionByAI(clickPosRow, clickPosCol);
                }
                else{
                    ui->playerLabel->setText(tr("玩家二落子"));
                }

            }
            update();
            break;
        }
    }

}


void MainWindow::countTime()
{
    QString s = QString::number(time--, 10);
    ui->lcdNumber->display(s);
}

void MainWindow::updateLabel()
{
    ui->timeLabel->setText(tr(" "));
}

void MainWindow::setFirstPlayer(int first)
{
    firstPlayer = first;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("../gobang/image/back.jpg");
    painter.drawPixmap(0, 24, pix);

    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    for(int i = 0; i < boardSize + 1; i++){
        //竖线
        painter.drawLine(boardMargin + blockSize * i, menuSize + boardMargin, boardMargin + blockSize * i, menuSize + boardMargin + blockSize * boardSize);
        //横线
        painter.drawLine(boardMargin, boardMargin + blockSize * i + menuSize,  boardMargin + blockSize * boardSize, boardMargin + blockSize * i + menuSize);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    for(int i = 0; i < boardSize + 1; i++){
        for(int j = 0; j < boardSize + 1; j++){
            if(game->gameMap[i][j] == 0){
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(boardMargin + blockSize * j - radius, menuSize + boardMargin + blockSize * i - radius, radius * 2, radius * 2);

            }
            else if(game->gameMap[i][j] == 1){
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(boardMargin + blockSize * j - radius, menuSize +boardMargin + blockSize * i - radius, radius * 2, radius * 2);
            }
            //标记最近下的子
            if(i == clickPosRow && j == clickPosCol){
                brush.setColor(Qt::red);
                painter.setBrush(brush);
                painter.drawEllipse(boardMargin + blockSize * j - smallRadius, menuSize + boardMargin + blockSize * i - smallRadius, smallRadius * 2, smallRadius * 2);
            }
        }
    }

    if(clickPosRow >= 0 && clickPosRow <= boardSize
            && clickPosCol >= 0 && clickPosCol <= boardSize
            &&game -> gameMap[clickPosRow][clickPosCol] != -1){
        //qDebug() << game->isWin(clickPosRow, clickPosCol);
        if(game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING){
            qDebug() << "win";
            game->gameStatus = WIN;

            QString str;
            if(game->gameMap[clickPosRow][clickPosCol] == 0){
                if(game->player1.getTurn() == 0){
                    str = "玩家一";
                    if(type == 1) str = "玩家";
                }
                else{
                    str = "玩家二";
                    if(type == 1) str = "电脑";
                }
            }
            else if(game->gameMap[clickPosRow][clickPosCol] == 1){
                if(game->player1.getTurn() == 1){
                    str = "玩家一";
                    if(type == 1) str = "玩家";
                }
                else{
                    str = "玩家二";
                    if(type == 1) str = "电脑";
                }
            }
            QMessageBox::StandardButton btnValue;
            if(type == 1 && str == "电脑"){
                //音效
                QSound::play("../gobang/sound/lose.wav");
                btnValue = QMessageBox::information(this, "啊哦", "您输了");
            }
            else if(type == 1 && str == "玩家"){
                //音效
                QSound::play("../gobang/sound/win.wav");
                btnValue = QMessageBox::information(this, "祝贺", "您获胜了！");
            }
            else{
                //音效
                QSound::play("../gobang/sound/win.wav");
                btnValue = QMessageBox::information(this, "祝贺", str + "获胜！");
            }


            //游戏重置
            if(btnValue == QMessageBox::Ok){
                count->stop();
                down->stop();
                clear->stop();
                this->close();
                welcome wel;
                rollDice roll;
                //MainWindow w;
                if(wel.exec() == QDialog::Accepted){
                    restart(wel.firstPlayer, wel.type);
                    this->show();
                }
            }
        }
    }

    if(game->isDeadGame()){
        QSound::play("../gobang/sound/lose.wav");
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "啊哦", "死局");
        if(btnValue == QMessageBox::Ok){
            count->stop();
            down->stop();
            clear->stop();
            this->close();
            welcome wel;
            rollDice roll;
            MainWindow w;
            if(wel.exec() == QDialog::Accepted){
                restart(wel.firstPlayer, wel.type);
                this->show();
            }
        }
    }
}

void MainWindow::restart(int first, int t)
{
    this->setFirstPlayer(first);
    setGameType(t);
    turn = 1;
    clickPosCol = -1;
    clickPosRow = -1;
    init();
    startTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    game = new Game;
    init();
}

void MainWindow::init()
{
    game->gameStatus = PLAYING;
    game->gameType = type;
    //qDebug() << type;
    game->startGame(firstPlayer);
    //qDebug() <<firstPlayer;
    if(firstPlayer == 2 && type == 1){
        qsrand(QDateTime::currentDateTime().toTime_t());
        clickPosCol = qrand() % boardSize;
        clickPosRow = qrand() % boardSize;
        game->gameMap[clickPosRow][clickPosCol] = !turn;
        //qDebug() << game->player2.getTurn();
        int tRow = clickPosRow, tCol = clickPosCol;
        game->actionByAI(clickPosRow, clickPosCol);
        game->gameMap[tRow][tCol] = -1;
        //clickPosCol = -1;
        //clickPosRow = -1;
        turn = !turn;
    }

    if(game->player1.getTurn() == turn){
        if(type == 0)
            ui->playerLabel->setText(tr("玩家一落子"));
        else
            ui->playerLabel->setText(tr("玩家落子"));
    }
    else{
        if(type == 0)
            ui->playerLabel->setText(tr("玩家二落子"));
        else
            ui->playerLabel->setText(tr("电脑落子"));

    }
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    //qDebug()<< event->pos();

    if(x >= boardMargin - posDelta && x < windowWidth - boardMargin + posDelta
            && y >= menuSize + boardMargin - posDelta && y < windowHeight - boardMargin + posDelta){
        int col = (x - boardMargin) / blockSize;
        int row = (y - boardMargin - menuSize) / blockSize;
        //最近的左上角的点
        int leftTopX = boardMargin + blockSize * col;
        int leftTopY = menuSize + boardMargin + blockSize * row;

        clickPosCol = -1;
        clickPosRow = -1;
        double len = 0;
        //左上
        len = sqrt((x - leftTopX) * (x - leftTopX) + (y - leftTopY) * (y - leftTopY));
        if(len <= posDelta){
            clickPosRow = row;
            clickPosCol = col;
        }
        //右上
        len = sqrt((x - leftTopX - blockSize) * (x - leftTopX - blockSize) + (y - leftTopY) * (y - leftTopY));
        if(len <= posDelta){
            clickPosCol = col + 1;
            clickPosRow = row;
        }
        //左下
        len = sqrt((x - leftTopX) * (x - leftTopX) + (y - leftTopY - blockSize) * (y - leftTopY - blockSize));
        if(len <= posDelta){
            clickPosCol = col;
            clickPosRow = row + 1;
        }
        //右下
        len = sqrt((x - leftTopX - blockSize) * (x - leftTopX - blockSize) + (y - leftTopY - blockSize) * (y - leftTopY - blockSize));
        if(len <= posDelta){
            clickPosCol = col + 1;
            clickPosRow = row + 1;
        }
    }

    if(game->gameMap[clickPosRow][clickPosCol] == -1){
        QSound::play("../gobang/sound/play.wav");
        game->gameMap[clickPosRow][clickPosCol] = turn;
        turn = !(turn);
        //qDebug() << turn;
        //qDebug() << game->player1.getTurn();
        //qDebug() << game->player2.getTurn();

        startTimer();
        clickError = false;
    }
    else{
        //提醒用户不能重复下子
        QSound::play("../gobang/sound/error.wav");
        clickError = true;
    }

    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if(!clickError){
        if(type == 1){
            //qDebug()<<clickPosRow;
            //qDebug()<<clickPosCol;
            turn = !turn;
            game->actionByAI(clickPosRow, clickPosCol);
            QSound::play("../gobang/sound/play.wav");
            ui->playerLabel->setText(tr("玩家落子"));
            update();
            startTimer();
        }
        else{
            if(turn == game->player1.getTurn()){
                ui->playerLabel->setText(tr("玩家一落子"));

            }
            else{
                ui->playerLabel->setText(tr("玩家二落子"));
            }
        }
    }
    else{
        clickError = false;
    }

}


void MainWindow::on_actionNew_triggered()
{
    count->stop();
    down->stop();
    clear->stop();
    this->close();
    welcome wel;
    rollDice roll;
    //MainWindow w;
    if(wel.exec() == QDialog::Accepted){
        //if(roll.exec() == QDialog::Accepted){
            restart(wel.firstPlayer, wel.type);
            this->show();
        //}
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "关于", "计科1605 王烟波 1030416505\n 于2018.05制作");
}
