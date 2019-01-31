#ifndef HW4_TRACER_H
#define HW4_TRACER_H


#include "Player.h"

class Tracer : public Player {
public:
    Tracer(uint id, int x, int y);

    // Name     : Tracer
    // Priority : { UP, LEFT, DOWN, RIGHT, ATTACK }

    // Armor    : BRICK
    // Weapon   : SHOVEL
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    ~Tracer() override ;

    Armor getArmor() const override ;

    Weapon getWeapon() const override ;

    std::vector<Move> getPriorityList() const override ;

    const std::string getFullName() const override ;

    Color::Code getColorID() const override ;
};


#endif //HW4_TRACER_H
