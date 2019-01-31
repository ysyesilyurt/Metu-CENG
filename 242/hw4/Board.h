#ifndef HW4_BOARD_H
#define HW4_BOARD_H


#include "Coordinate.h"
#include "Player.h"
#include <vector>

class Board {
private:
    const uint boardSize;
    std::vector<Player *> *players;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PRIVATE METHODS/PROPERTIES BELOW

    uint stormSize;
    
public:
    Board(uint boardSize, std::vector<Player *> *players);
    ~Board();

    uint getSize() const;
    /**
     * Decide whether the coordinate is in the board limits.
     *
     * @param coord Coordinate to search.
     * @return true if coord is in limits, false otherwise.
     */
    bool isCoordInBoard(const Coordinate& coord) const;
    /**
     * Decide whether the given coordinate is in storm.
     *
     * @param coord Coordinate to search.
     * @return true if covered in storm, false otherwise.
     */
    bool isStormInCoord(const Coordinate &coord) const;

    /**
     * Decide whether the given coordinate is the hill.
     *
     * @param coord Coordinate to search.
     * @return true if the coord is at the very center of the board, false otherwise.
     */
    bool isCoordHill(const Coordinate& coord) const;
    /**
     * Indexing.
     *
     * Find the player in coordinate.
     *
     * nullptr if player does not exists in given coordinates, or !isCoordInBoard
     *
     * @param coord  The coordinate to search.
     * @return The player in coordinate.
     */
    Player *operator[](const Coordinate& coord) const;
    /**
     * Calculate the new coordinate with the given move and coordinate.
     *
     * NOOP and ATTACK are no-op, return coord.
     *
     * The new coordinate cannot be outside of the borders.
     * If it's the case, return coord.
     *
     * Also, if there's another player in the new coordinate,
     * return coord.
     *
     * @param move Move to be made.
     * @param coord The coordinate to be moved.
     * @return Calculated coordinate after the move.
     */
    Coordinate calculateCoordWithMove(Move move, const Coordinate &coord) const;

    /**
     * Find the visible coordinates from given coordinate.
     *
     * Explanation: The immediate UP/DOWN/LEFT/RIGHT tiles must be calculated.
     *
     * There could be max of 4 tiles, and min of 2 tiles (on corners).
     * Every found coordinate must be in the board limits.
     *
     * If the given coordinate is not in board, return a vector with size = 0. Order does NOT matter.
     *
     * Example:
     *
     * 01----
     * 02HH--
     * ------
     *
     * visibleCoordsFromCoord(Coordinate(0, 0)) == { (1, 0), (0, 1) }
     * visibleCoordsFromCoord(Coordinate(1, 1)) == { (1, 0), (2, 1), (1, 2), (0, 1) }
     * visibleCoordsFromCoord(Coordinate(-1, 0)) == { }
     *
     * @param coord The coordinate to search.
     * @return All coordinates visible.
     */
    std::vector<Coordinate> visibleCoordsFromCoord(const Coordinate &coord) const;

    /**
     * Calculate the storm according to the currentRound.
     *
     * @param currentRound The current round being played.
     */
    void updateStorm(uint currentRound);

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW

    Coordinate getHillCoord() const;

};


#endif //HW4_BOARD_H
