#include "Berserk.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Berserk::Berserk(uint id, int x, int y) : Player(id,x,y)
{
    Player::HP = 100;
}

Berserk::~Berserk() = default;

Armor Berserk::getArmor() const
{
    return WOODEN;
}

Weapon Berserk::getWeapon() const
{
    return PISTOL;
}

std::vector<Move> Berserk::getPriorityList() const
{
    std::vector<Move> plist = {ATTACK, UP, LEFT, DOWN, RIGHT};
    return plist;
}

const std::string Berserk::getFullName() const
{
    return "Berserk" + getBoardID();
}

Color::Code Berserk::getColorID() const
{
    return Color::FG_RED;
}