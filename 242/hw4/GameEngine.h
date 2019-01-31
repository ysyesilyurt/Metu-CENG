#ifndef HW4_GAMEENGINE_H
#define HW4_GAMEENGINE_H

#include <vector>
#include "Board.h"

class GameEngine {
private:
    uint currentRound;
    Board board;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PRIVATE METHODS/PROPERTIES BELOW

    std::vector<Player *> * playerVector;

public:
    /**
     * Constructor.
     *
     * GameEngine "owns" these players.
     * GameEngine also "owns" the vector.
     *
     * @param boardSize The side length of the board.
     * @param players All players to participate in the game.
     */
    GameEngine(uint boardSize, std::vector<Player *> *players);
    ~GameEngine();

    const Board& getBoard() const;

    /**
     * Indexing.
     *
     * Find the player with given ID.
     *
     * nullptr if not exists.
     *
     * @param id ID of the player.
     * @return The player with given ID.
     */
    Player* operator[](uint id) const;

    /**
     * Decide whether the game is finished.
     *
     * @return true if there is only 1 player (alive), on top of the hill; or there are 0 players. False otherwise.
     */
    bool isFinished() const;

    /**
     * Take turn for every player.
     *
     * How-to:
     * - Announce turn start (cout).
     * Example: -- START ROUND 1  --
     * - board.updateStorm(currentRound)
     * - For every player (sorted according to their IDs) that isn't dead (HP <= 0):
     *      - takeTurnForPlayer(player).
     * - Announce turn end (cout).
     * Example: -- END ROUND 1 --
     */
    void takeTurn();

    /**
     * The most important (algorithm-wise) method.
     *
     * How-to:
     * - Get player with ID. Return NOOP if not exists.
     * - Get player's priority list.
     * - Get player's visibility from the board (visibleCoordsFromCoord).
     *
     * - If the player is in the storm (isStormInCoord), announce the damage and give player stormDamage.
     * - Example: Tracer01(10) is STORMED! (-10)
     *
     * - If dead, announce the death, remove player from the board/list/anywhere, and return NOOP.
     * - Example: Tracer01(0) DIED.
     *
     * - For MOVE in player's priority list:
     *          - If the MOVE is NOOP:
     *              - return NOOP.
     *          - Else if the MOVE is ATTACK:
     *              - Get all players that this player can attack (board[coord] for each in visibilityCoords).
     *              - If none, continue.
     *              - Else:
     *                  - Pick the one with most priority (lowest ID).
     *                  - isPlayerDead = player.attackTo(thatPlayer).
     *                  - if isPlayerDead:
     *                      - announce the death.
     *                      - remove thatPlayer from the board/list/anywhere.
     *                  - return ATTACK.
     *          - Else (UP/DOWN/LEFT/RIGHT):
     *              - calculateCoordWithMove(move).
     *              - If the new coordinate is different than the player's (meaning it's able to do that move)
     *              AND the player is getting closer to the hill;
     *                  - player.executeMove(MOVE).
     *                  - return MOVE.
     *              - Else:
     *                  - continue.
     *
     * // If the priority list is exhausted;
     * return NOOP.
     *
     * @param player Player ID to move.
     * @return move Decided move.
     */
    Move takeTurnForPlayer(uint playerID);

    /**
     * Find the winner player.
     *
     * nullptr if there are 0 players left, or the game isn't finished yet.
     *
     * @return The winner player.
     */
    Player *getWinnerPlayer() const;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW

    bool anybodyDied;

    bool diedFromWhere; // false = from left or itself , true = from right of the player
    
};


#endif //HW4_GAMEENGINE_H
