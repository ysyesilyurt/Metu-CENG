#ifndef HW4_BERSERK_H
#define HW4_BERSERK_H


#include "Player.h"

class Berserk : public Player {

public:
    Berserk(uint id, int x, int y);
    // Name     : Berserk
    // Priority : { ATTACK, UP, LEFT, DOWN, RIGHT }

    // Armor    : WOODEN
    // Weapon   : PISTOL
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    ~Berserk() override ;

    Armor getArmor() const override ;

    Weapon getWeapon() const override ;

    std::vector<Move> getPriorityList() const override ;

    const std::string getFullName() const override ;

    Color::Code getColorID() const override ;

};


#endif //HW4_BERSERK_H
