#ifndef PLAYER_H
#define PLAYER_H

#include <QTimer>

class Player
{
public:
    Player();
    ~Player();
    void setTurn(bool flag);
    bool getTurn();
    int getID();
    void setID(int id);
    int getColor();
    void setColor(int flag);

private:
    bool turnFlag;
    int id;
    int color;
    QTimer myTimer;

};

#endif // PLAYER_H
