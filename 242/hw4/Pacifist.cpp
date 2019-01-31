#include "Pacifist.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Pacifist::Pacifist(uint id, int x, int y) : Player(id,x,y)
{
    Player::HP = 100;
}

Pacifist::~Pacifist() = default;

Armor Pacifist::getArmor() const
{
    return METAL;
}

Weapon Pacifist::getWeapon() const
{
    return NOWEAPON;
}

std::vector<Move> Pacifist::getPriorityList() const
{
    std::vector<Move> plist = {UP, LEFT, DOWN, RIGHT};
    return plist;
}

const std::string Pacifist::getFullName() const
{
    return "Pacifist" + getBoardID();
}

Color::Code Pacifist::getColorID() const
{
    return Color::FG_GREEN;
}