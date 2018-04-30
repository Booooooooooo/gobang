#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <player.h>
using namespace std;

const int boardSize = 14;
enum GameStatus{
    PLAYING,
    WIN,
    DEAD
};

class Game
{
public:
    Game();
    ~Game();
    bool startGame(int firstPlayer);//返回1表示游戏开始，开启计时器
    void updateGameMap(int row, int col);
    bool isWin(int row, int col);
    bool isDeadGame();
    Player player1;
    Player player2;
    vector < vector<int> > gameMap;//棋盘和棋子的情况，空白为-1，白子0，黑子1
    GameStatus gameStatus;

private:
    int playerFlag;
};

#endif // GAME_H
