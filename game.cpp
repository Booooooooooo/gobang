#include "game.h"
#include <QTime>
#include <QDebug>
#include <QTime>
#include <QApplication>

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

    if(firstPlayer == 1){
        player1.setTurn(1);
        player2.setTurn(0);
    }
    else{
        player1.setTurn(0);
        player2.setTurn(1);
    }
    /*playerFlag = firstPlayer % 2;
    if(player1.getID() == playerFlag){
        player1.setTurn(1);
        player2.setTurn(0);
        player1.setColor(1);
        player2.setColor(0);
    }
    else{
        player2.setTurn(1);
        player2.setColor(1);
        player1.setTurn(0);
        player1.setColor(0);
    }*/

    if(gameType == 1){
        scoreMap.clear();
        for(int i = 0; i < boardSize + 1; i++){
            vector<int> lineScores;
            for(int j = 0; j < boardSize; j++){
                lineScores.push_back(0);
            }
            scoreMap.push_back(lineScores);
        }
    }
}

void Game::actionByAI(int &clickRow, int &clickCol)
{
    calculateScore();

    int maxScore = 0;
    vector< pair<int, int> > maxPoints;
    for(int row = 0; row < boardSize + 1; row++){
        for(int col = 0; col < boardSize + 1; col++){
            if(gameMap[row][col] == -1){
                if(scoreMap[row][col] > maxScore){
                    maxPoints.clear();
                    maxScore = scoreMap[row][col];
                    maxPoints.push_back(make_pair(row, col));
                }
                else if(scoreMap[row][col] == maxScore){
                    maxPoints.push_back(make_pair(row, col));
                }
            }
        }
    }

    qsrand(QDateTime::currentDateTime().toTime_t());
    int index = qrand() % maxPoints.size();
    pair<int, int> pointPair = maxPoints.at(index);
    clickRow = pointPair.first;
    clickCol = pointPair.second;
    gameMap[clickRow][clickCol] = player2.getTurn();
    //qDebug()<<player2.getTurn();
    sleep(500);
}

void Game::sleep(unsigned int msec)
{
     QTime reachTime = QTime::currentTime().addMSecs(msec);
     while(QTime::currentTime() < reachTime){
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     }
}

void Game::calculateScore()
{
    int personNum = 0;
    int comNum = 0;
    int emptyNum = 0;

    scoreMap.clear();
    for(int i = 0; i < boardSize + 1; i++){
        vector<int> lineScores;
        for(int j = 0; j < boardSize + 1; j++){
            lineScores.push_back(0);
        }
        scoreMap.push_back(lineScores);
    }

    for(int row = 0; row < boardSize + 1; row++){
        for(int col = 0; col < boardSize + 1; col++){
            if(row >= 0 && col >= 0 && gameMap[row][col] == -1){
                for(int y = -1; y <= 1; y++){
                    for(int x = -1; x <= 1; x++){
                        personNum = 0;
                        comNum = 0;
                        emptyNum = 0;

                        if(!(y == 0 && x == 0)){
                            for(int i = 1; i <= 4; i++){
                                if(row + i * y >= 0 && row + i * y <= boardSize
                                        && col + i * x >= 0 && col + i * x <= boardSize
                                        && gameMap[row + i * y][col + i * x] == player1.getTurn()){
                                    personNum++;
                                }
                                else if(row + i * y >= 0 && row + i * y <= boardSize
                                        && col + i * x >= 0 && col + i * x <= boardSize
                                        && gameMap[row + i * y][col + i * x] == -1){
                                    emptyNum++;
                                    break;
                                }
                                else{
                                    break;
                                }
                            }

                            for(int i = 1; i <= 4; i++){
                                if(row - i * y >= 0 && row - i * y <= boardSize
                                        && col - i * x >= 0 && col - i * x <= boardSize
                                        && gameMap[row - i * y][col - i * x] == player1.getTurn()){
                                    personNum++;
                                }
                                else if(row - i * y >= 0 && row - i * y <= boardSize
                                        && col - i * x >= 0 && col - i * x <= boardSize
                                        && gameMap[row - i * y][col - i * x] == -1){
                                    emptyNum++;
                                    break;
                                }
                                else{
                                    break;
                                }
                            }

                            if(personNum == 1)
                                scoreMap[row][col] += 10;
                            else if(personNum == 2){
                                if(emptyNum == 1)
                                    scoreMap[row][col] += 30;
                                else if(emptyNum == 2)
                                    scoreMap[row][col] += 40;
                            }
                            else if(personNum == 3){
                                if(emptyNum == 1)
                                    scoreMap[row][col] += 60;
                                else if(emptyNum == 2)
                                    scoreMap[row][col] += 110;
                            }
                            else if(personNum == 4)
                                scoreMap[row][col] += 10100;

                            emptyNum = 0;

                            for(int i = 1; i <= 4; i++){
                                if(row + i * y >= 0 && row + i * y <= boardSize
                                        && col + i * x >= 0 && col + i * x <= boardSize
                                        && gameMap[row + i * y][col + i * x] == player2.getTurn()){
                                    comNum++;
                                }
                                else if(row + i * y >= 0 && row + i * y <= boardSize
                                        && col + i * x >= 0 && col + i * x <= boardSize
                                        && gameMap[row + i * y][col + i * x] == -1){
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }

                            for(int i = 1; i <= 4; i++){
                                if(row - i * y >= 0 && row - i * y <= boardSize
                                        && col - i * x >= 0 && col - i * x <= boardSize
                                        && gameMap[row - i * y][col - i * x] == player2.getTurn()){
                                    comNum++;
                                }
                                else if(row - i * y >= 0 && row - i * y <= boardSize
                                        && col - i * x >= 0 && col - i * x <= boardSize
                                        && gameMap[row - i * y][col - i * x] == -1){
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }

                            if(comNum == 0)
                                scoreMap[row][col] += 5;
                            else if(comNum == 1)
                                scoreMap[row][col] += 10;
                            else if(comNum == 2){
                                if(emptyNum == 1)
                                    scoreMap[row][col] += 25;
                                else if(emptyNum == 2)
                                    scoreMap[row][col] += 50;
                            }
                            else if(comNum == 3){
                                if(emptyNum == 1)
                                    scoreMap[row][col] += 55;
                                else if(emptyNum == 2)
                                    scoreMap[row][col] += 100;
                            }
                            else if(comNum >= 4)
                                scoreMap[row][col] += 10000;
                        }
                    }
                }
            }
        }
    }
}

bool Game::isWin(int row, int col)
{
    //根据当前落子情况遍历5个棋子

    //水平
    for(int i = 0; i < 5; i++){
        //向左i个开始
        if(col - i >= 0 && col - i + 4 <= boardSize
                && gameMap[row][col - i] == gameMap[row][col - i + 1]
                && gameMap[row][col - i] == gameMap[row][col - i + 2]
                && gameMap[row][col - i] == gameMap[row][col - i + 3]
                && gameMap[row][col - i] == gameMap[row][col - i + 4]
                && gameMap[row][col - i] != -1)
            return true;
    }

    //竖直
    for(int i = 0; i < 5; i++){
        if(row - i >= 0 && row - i + 4 <= boardSize
                && gameMap[row - i][col] == gameMap[row - i + 1][col]
                && gameMap[row - i][col] == gameMap[row - i + 2][col]
                && gameMap[row - i][col] == gameMap[row - i + 3][col]
                && gameMap[row - i][col] == gameMap[row - i + 4][col]
                && gameMap[row - i][col] != -1)
            return true;
    }

    //左斜
    for(int i = 0; i < 5; i++){
        if(row + i <= boardSize && row + i - 4 >= 0 && col - i + 4 <= boardSize
                && gameMap[row + i][col - i] == gameMap[row + i - 1][col - i + 1]
                && gameMap[row + i][col - i] == gameMap[row + i - 2][col - i + 2]
                && gameMap[row + i][col - i] == gameMap[row + i - 3][col - i + 3]
                && gameMap[row + i][col - i] == gameMap[row + i - 4][col - i + 4]
                && gameMap[row + i][col - i] != -1)
            return true;
    }

    //右斜
    for(int i = 0; i < 5; i++){
        if(row - i >= 0 && row - i + 4 <= boardSize && col - i >= 0 && col - i + 4 <= boardSize
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
    for(int i = 0; i < boardSize + 1; i++){
        for(int j = 0; j < boardSize + 1; j++){
            if(!(gameMap[i][j] == 1 || gameMap[i][j] == 0))
                return false;
        }
    }
    return true;
}


