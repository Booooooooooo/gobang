#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <game.h>
#include <QMouseEvent>

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
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseResleaseEvent(QMouseEvent *event);
private:
    Game *game;
    Ui::MainWindow *ui;
    int time;//计时数字
    int clickPosRow, clickPosCol;
    void initGame();
    void checkGame(int y, int x);
    int turn;//0为黑子走，1为白子走
    int firstPlayer;
    void restart(int first);
private slots:
    void countTime();
    void countDown();
    void updateLabel();
    //void chessOne();
    void init();
};

#endif // MAINWINDOW_H
