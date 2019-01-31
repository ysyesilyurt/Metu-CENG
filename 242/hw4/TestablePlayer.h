#ifndef HW4_TESTABLEPLAYER_H
#define HW4_TESTABLEPLAYER_H


#include "Testable.h"
#include "Player.h"

class TestablePlayer : public Testable {
private:
    void runInternal() override;

    void checkPlayer(Player *player,
                     int correctHP,
                     Armor correctArmor,
                     Weapon correctWeapon,
                     const std::string& correctFullName,
                     const std::vector<Move>& correctPriorityList);
public:
    TestablePlayer() : Testable("Player Test", 15) { }
};


#endif //HW4_TESTABLEPLAYER_H
