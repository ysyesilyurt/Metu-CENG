#ifndef HW4_AMBUSHER_H
#define HW4_AMBUSHER_H


#include "Player.h"

class Ambusher : public Player {
public:
    Ambusher(uint id, int x, int y);

    // Name     : Ambusher
    // Priority : { ATTACK }

    // Armor    : NOARMOR
    // Weapon   : SEMIAUTO
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    ~Ambusher() override ;

    Armor getArmor() const override ;

    Weapon getWeapon() const override ;

    std::vector<Move> getPriorityList() const override ;

    const std::string getFullName() const override ;

    Color::Code getColorID() const override ;
};


#endif //HW4_AMBUSHER_H
