#ifndef HW4_ENTITY_H
#define HW4_ENTITY_H

// engin: DO NOT MODIFY THIS FILE.

#define STORM_WIDTH_COEFF 5
#define STORM_DAMAGE_PER_LEVEL 5

enum Move {
    NOOP = -1,
    ATTACK = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
};

enum Weapon {
    NOWEAPON,       // None
    SHOVEL,         // Low
    PISTOL,         // Mid
    SEMIAUTO        // High
};

enum Armor {
    NOARMOR,        // None
    WOODEN,         // Low
    BRICK,          // Mid
    METAL,          // High
};


namespace Entity {

    static uint stormWidthForRound(uint currentRound) {
        return (currentRound - 1) / STORM_WIDTH_COEFF;
    }
    static int stormDamageForRound(uint currentRound) {
        return stormWidthForRound(currentRound) * STORM_DAMAGE_PER_LEVEL;
    }

    static int damageForWeapon(Weapon weapon) {
        switch(weapon) {
            case NOWEAPON:
                return 0;
            case SHOVEL:
                return 15;
            case PISTOL:
                return 20;
            case SEMIAUTO:
                return 25;
        }
    }

    static int damageReductionForArmor(Armor armor) {
        switch(armor) {
            case NOARMOR:
                return 0;
            case WOODEN:
                return 5;
            case BRICK:
                return 10;
            case METAL:
                return 15;
        }
    }
}

#endif //HW4_ENTITY_H
