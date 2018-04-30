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

const int menuSize = 24;//菜单栏宽度
const int boardMargin = 30;//棋盘边缘
const int radius = 15;//棋子半径
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
    //this->setWindowModality(Qt::ApplicationModal);
    //this->firstPlayer = firstPlayer;
    setIconSize(QSize(menuSize, menuSize));
    this->resize(windowWidth,windowHeight);
    ui->lcdNumber->setParent(this);
    ui->lcdNumber->setStyleSheet("border: 1px solid black; background: white");
    ui->lcdNumber->setGeometry(boardMargin + 5 * blockSize, menuSize  + boardSize * blockSize + boardMargin * 2, windowWidth / 4, displaySize);
    ui->playerLabel->setParent(this);
    ui->playerLabel->setGeometry(boardMargin, menuSize + boardSize * blockSize + boardMargin * 2, windowWidth / 4, displaySize);
    ui->playerLabel->setFont(QFont("Timers", 12, QFont::Bold));
    ui->timeLabel->setParent(this);
    ui->timeLabel->setFont(QFont("TImers", 12, QFont::Bold));
    ui->timeLabel->setGeometry(boardMargin + 10 * blockSize,boardSize * blockSize + boardMargin * 2, windowWidth / 4, displaySize);
    turn = 1;
    initGame();

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

void MainWindow::countDown()
{
    ui->timeLabel->setText(tr("超时！"));
    time = 1;
}


void MainWindow::countTime()
{
    QString s = QString::number(time++, 10);
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
        }
    }

    if(clickPosRow > 0 && clickPosRow < boardSize
            && clickPosCol && clickPosCol < boardSize
            && (game->gameMap[clickPosRow][clickPosCol] == 1 || game->gameMap[clickPosRow][clickPosCol] == -1)){
        if(game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING){
            qDebug() << "win";
            game->gameStatus = WIN;
            //音效
            //QSound::play(WIN_SOUND);
            QString str;
            if(game->gameMap[clickPosRow][clickPosCol] == 0){
                str = "white player";
            }
            else if(game->gameMap[clickPosRow][clickPosCol] == 1){
                str = "black player";
            }
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + "win!");

            //游戏重置
            if(btnValue == QMessageBox::Ok){
                this->close();
                welcome wel;
                rollDice roll;
                //MainWindow w;
                if(wel.exec() == QDialog::Accepted){
                    if(roll.exec() == QDialog::Accepted){
                        restart(roll.getFirst());
                        this->show();
                    }
                }
            }
        }
    }

    if(game->isDeadGame()){
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
        if(btnValue == QMessageBox::Ok){
            this->close();
            welcome wel;
            rollDice roll;
            MainWindow w;
            if(wel.exec() == QDialog::Accepted){
                if(roll.exec() == QDialog::Accepted){
                    restart(roll.getFirst());
                    this->show();
                }
            }
        }
    }
}

void MainWindow::restart(int first)
{
    this->setFirstPlayer(first);
    turn = 1;
    game->startGame(first);
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
    game->startGame(firstPlayer);
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    qDebug()<< event->pos();

    if(x >= boardMargin && x < windowWidth - boardMargin
            && y >= menuSize + boardMargin && y < windowHeight - boardMargin){
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
        game->gameMap[clickPosRow][clickPosCol] = turn;
        turn = !(turn);
    }

    update();
}

