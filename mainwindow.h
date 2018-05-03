#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <game.h>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFirstPlayer(int first);
    void startTimer();
    void setGameType(int type);
    void restart(int first, int t);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Game *game;
    int type;
    Ui::MainWindow *ui;
    int time;//计时数字
    int clickPosRow, clickPosCol;
    void initGame();
    void checkGame(int y, int x);
    int turn;//0为黑子走，1为白子走
    int firstPlayer;
    bool clickError;

    QTimer* down;
    QTimer* clear;
    QTimer* count;
private slots:
    void countTime();
    void countDown();
    void updateLabel();
    //void chessOne();
    void init();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
