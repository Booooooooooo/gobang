#include "game.h"

Game::Game()
{

}

Game::~Game()
{

}


bool Game::startGame(int firstPlayer)
{
    gameMap.clear();
    for(int i = 0; i < boardSize + 1; i++){
        vector <int> lineBoard;
        for(int j = 0; j < boardSize + 1; j++){
            lineBoard.push_back(-1);
        }
        gameMap.push_back(lineBoard);
    }

    playerFlag = firstPlayer % 2;
    if(player1.getID() == firstPlayer){
        player1.setTurn(true);
        player2.setTurn(false);
        player1.setColor(true);
        player2.setColor(false);
    }
    else{
        player2.setTurn(true);
        player2.setColor(true);
        player1.setTurn(false);
        player1.setColor(false);
    }
}

bool Game::isWin(int row, int col)
{
    //根据当前落子情况遍历5个棋子

    //水平
    for(int i = 0; i < 5; i++){
        //向左i个开始
        if(col - i >= 0 && col - i + 4 < boardSize
                && gameMap[row][col - i] == gameMap[row][col - i + 1]
                && gameMap[row][col - i] == gameMap[row][col - i + 2]
                && gameMap[row][col - i] == gameMap[row][col - i + 3]
                && gameMap[row][col - i] == gameMap[row][col - i + 4]
                && gameMap[row][col - i] != -1)
            return true;
    }

    //竖直
    for(int i = 0; i < 5; i++){
        if(row - i >= 0 && row - i + 4 < boardSize
                && gameMap[row - i][col] == gameMap[row - i + 1][col]
                && gameMap[row - i][col] == gameMap[row - i + 2][col]
                && gameMap[row - i][col] == gameMap[row - i + 3][col]
                && gameMap[row - i][col] == gameMap[row - i + 4][col]
                && gameMap[row - i][col] != -1)
            return true;
    }

    //左斜
    for(int i = 0; i < 5; i++){
        if(row + i < boardSize && row + i - 4 >= 0 && col - i + 4 < boardSize
                && gameMap[row + i][col - i] == gameMap[row + i - 1][col - i + 1]
                && gameMap[row + i][col - i] == gameMap[row + i - 2][col - i + 2]
                && gameMap[row + i][col - i] == gameMap[row + i - 3][col - i + 3]
                && gameMap[row + i][col - i] == gameMap[row + i - 4][col - i + 4]
                && gameMap[row + i][col - i] != -1)
            return true;
    }

    //右斜
    for(int i = 0; i < 5; i++){
        if(row - i >= 0 && row - i + 4 < boardSize && col - i >= 0 && col - i + 4 < boardSize
                && gameMap[row - i][col - i] == gameMap[row - i + 1][col - i + 1]
                && gameMap[row - i][col - i] == gameMap[row - i + 2][col - i + 2]
                && gameMap[row - i][col - i] == gameMap[row - i + 3][col - i + 3]
                && gameMap[row - i][col - i] == gameMap[row - i + 4][col - i + 4]
                && gameMap[row - i][col - i] != -1)
            return true;
    }

    return false;
}


bool Game::isDeadGame()
{
    for(int i = 1; i < boardSize + 1; i++){
        for(int j = 1; j < boardSize + 1; j++){
            if(!(gameMap[i][j] == 1 || gameMap[i][j] == 0))
                return false;
        }
    }
    return true;
}


