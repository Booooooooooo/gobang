#include "player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::setTurn(int turn)
{
    turnFlag = turn;
}

int Player::getTurn()
{
    return turnFlag;
}

void Player::setColor(int flag)
{
    color = flag;
}

int Player::getColor()
{
    return color;
}

void Player::setID(int id)
{
    this->id = id;
}

int Player::getID()
{
    return id;
}
