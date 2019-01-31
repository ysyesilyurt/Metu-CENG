#ifndef HW4_PACIFIST_H
#define HW4_PACIFIST_H


#include "Player.h"

class Pacifist : public Player {
public:
    Pacifist(uint id, int x, int y);

    // Name     : Pacifist
    // Priority : { UP, LEFT, DOWN, RIGHT }

    // Armor    : METAL
    // Weapon   : NOWEAPON
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    ~Pacifist() override ;

    Armor getArmor() const override ;

    Weapon getWeapon() const override ;

    std::vector<Move> getPriorityList() const override ;

    const std::string getFullName() const override ;

    Color::Code getColorID() const override ;
};


#endif //HW4_PACIFIST_H
