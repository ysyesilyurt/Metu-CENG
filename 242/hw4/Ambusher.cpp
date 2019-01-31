#include "Ambusher.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Ambusher::Ambusher(uint id, int x, int y) : Player(id,x,y)
{
    Player::HP = 100;
}

Ambusher::~Ambusher() = default;

Armor Ambusher::getArmor() const
{
    return NOARMOR;
}

Weapon Ambusher::getWeapon() const
{
    return SEMIAUTO;
}

std::vector<Move> Ambusher::getPriorityList() const
{
    std::vector<Move> plist = {ATTACK};
    return plist;
}

const std::string Ambusher::getFullName() const
{
    return "Ambusher" + getBoardID();
}

Color::Code Ambusher::getColorID() const
{
    return Color::FG_BLUE;
}