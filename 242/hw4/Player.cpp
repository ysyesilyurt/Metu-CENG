#include <iostream>
#include "Player.h"
#include <algorithm>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Player::Player(uint idd, int x, int y) : id(idd) , coordinate(x,y)
{

}

Player::~Player() = default;

uint Player::getID() const
{
    return id;
}

const Coordinate& Player::getCoord() const
{
    return coordinate;
}

int Player::getHP() const
{
    return HP;
}

std::string Player::getBoardID() const
{
    if(id < 10)
        return "0" + std::to_string(id);
    else
        return std::to_string(id);
}

bool Player::isDead() const
{
    if(HP <= 0)
        return true;
    else
        return false;
}

void Player::executeMove(Move move) // Important note: Priority list does NOT matter here.
{
    coordinate = coordinate + move;
    if(move == NOOP || move == ATTACK)
        return;
    else
    {
        switch (move)
        {
            case UP:
                std::cout << getFullName() + "("+ std::to_string(getHP()) + ")" + " moved UP.\n";
                break;
            case DOWN:
                std::cout << getFullName() + "("+ std::to_string(getHP()) + ")" + " moved DOWN.\n";
                break;
            case LEFT:
                std::cout << getFullName() + "("+ std::to_string(getHP()) + ")" + " moved LEFT.\n";
                break;
            case RIGHT:
                std::cout << getFullName() + "("+ std::to_string(getHP()) + ")" + " moved RIGHT.\n";
                break;
        }
    }
}

bool Player::attackTo(Player *player) // Important note: Priority list does NOT matter here.
{
    if(this == player)
        return false;
    std::cout << getFullName() + "("+ std::to_string(getHP()) + ")" + " ATTACKED " + player->getFullName() + "("+ std::to_string(player->getHP()) + ")! (-" + std::to_string(std::max((Entity::damageForWeapon(getWeapon()) - Entity::damageReductionForArmor(player->getArmor())),0)) + ")\n";
    player->HP -= std::max((Entity::damageForWeapon(getWeapon()) - Entity::damageReductionForArmor(player->getArmor())),0);
    return player->isDead();
}

bool Player::comparePlayers(const Player * player1, const Player * player2)
{
    return (player1->getID() < player2->getID());
}

void Player::setHP(int newHP)
{
    HP = newHP;
}