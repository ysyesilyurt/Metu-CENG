#ifndef HW4_PLAYER_H
#define HW4_PLAYER_H

#include "Color.h"
#include "Coordinate.h"
#include "Entity.h"

#include <vector>

class Player {
protected:
    const uint id;
    Coordinate coordinate;

    int HP;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PROTECTED METHODS/PROPERTIES BELOW

public:
    /**
     * Main Constructor.
     *
     * @param id The ID of the player. [0-100).
     * @param x X-coordinate of the player.
     * @param y Y-coordinate of the player.
     */
    Player(uint id, int x, int y);
    virtual ~Player();

    uint getID() const;
    const Coordinate& getCoord() const;

    int getHP() const;

    /**
     * Board ID is two-decimal ID for the Player.
     *
     * Player ID = 0, 91
     * Board ID = "00", "91"
     *
     * @return BoardID of the user.
     */
    std::string getBoardID() const;

    virtual Armor getArmor() const = 0;
    virtual Weapon getWeapon() const = 0;

    /**
     * Every player has a different priority move list.
     * It's explained in the Players' header.
     *
     * @return The move priority list for the player.
     */
    virtual std::vector<Move> getPriorityList() const = 0;

    /**
     * Get the full name of the player.
     *
     * Example (Tracer with ID 92) = "Tracer92"
     * Example (Tracer with ID 1)  = "Tracer01"
     *
     * @return Full name of the player.
     */
    virtual const std::string getFullName() const = 0;

    /**
     * Decide whether the player is dead.
     *
     * @return true if the player's hp <= 0, false otherwise.
     */
    bool isDead() const;
    /**
     * Execute the given move for the player's coordinates.
     *
     * Important note: Priority list does NOT matter here.
     *
     * NOOP and ATTACK are no-op.
     *
     * Do not forget to print the move.
     * "-playerFullName(playerHP)- moved UP/DOWN/LEFT/RIGHT."
     *
     * "Tracer00(100) moved UP."
     *
     * @param move Move to make.
     */
    void executeMove(Move move);

    /**
     * Attack the given player, and decide whether the attacked player is dead.
     *
     * Important note: Priority list does NOT matter here.
     *
     * Formulae : RHS's HP -= max((LHS's damage - RHS's armor), 0)
     *
     * Do not forget to print the attack.
     *
     * "-lhsFullName(lhsHP)- ATTACKED -rhsFullName(rhsHP)-! (-damageDone-)
     *
     * "Tracer00(100) ATTACKED Tracer01(100)! (-10)"
     *
     * @param player Player to be attacked.
     * @return true if attacked player is dead, false otherwise.
     */
    bool attackTo(Player *player);

    /**
     * Return different colors for different Player classes (override!).
     *
     * Note: This method is optional. You may leave this as-is.
     *
     * @return The associated color code with the class.
     */
    virtual Color::Code getColorID() const { return Color::FG_DEFAULT; }

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW

    static bool comparePlayers(const Player * player1, const Player * player2); // returns true if id1 < id2

    void setHP(int newHP);
};


#endif //HW4_PLAYER_H
