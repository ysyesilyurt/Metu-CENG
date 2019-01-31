#include "Tracer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Tracer::Tracer(uint id, int x, int y) : Player(id,x,y)
{
    Player::HP = 100;
}

Tracer::~Tracer() = default;

Armor Tracer::getArmor() const
{
    return BRICK;
}

Weapon Tracer::getWeapon() const
{
    return SHOVEL;
}

std::vector<Move> Tracer::getPriorityList() const
{
    std::vector<Move> plist = {UP, LEFT, DOWN, RIGHT, ATTACK};
    return plist;
}

const std::string Tracer::getFullName() const
{
    return "Tracer" + getBoardID();
}

Color::Code Tracer::getColorID() const
{
    return Color::FG_YELLOW;
}