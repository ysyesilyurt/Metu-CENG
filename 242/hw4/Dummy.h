#ifndef HW4_DUMMY_H
#define HW4_DUMMY_H


#include "Player.h"

class Dummy : public Player {
public:
    Dummy(uint id, int x, int y);

    // Name     : Dummy
    // Priority : { NOOP }

    // Armor    : NOARMOR
    // Weapon   : NOWEAPON
    // HP       : 1000

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    ~Dummy() override ;

    Armor getArmor() const override ;

    Weapon getWeapon() const override ;

    std::vector<Move> getPriorityList() const override ;

    const std::string getFullName() const override ;

    Color::Code getColorID() const override ;
};


#endif //HW4_DUMMY_H
