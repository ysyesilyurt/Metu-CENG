#ifndef HW4_COORDINATE_H
#define HW4_COORDINATE_H

// engin: DO NOT MODIFY THIS FILE.

#include <ostream>
#include "Entity.h"

struct Coordinate {
    int x, y;

    Coordinate(int x, int y) : x(x), y(y) { }

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
        os << "(" << coord.x << "/" << coord.y << ")";

        return os;
    }

    bool operator<(const Coordinate &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    bool operator==(const Coordinate &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Coordinate &rhs) const {
        return !((*this) == rhs);
    }

    /**
     * Use this!
     *
     * @param move Move to be made.
     * @return New coordinate with the given move.
     */
    Coordinate operator+(Move move) const {
        int newX = x;
        int newY = y;

        switch(move) {
            case NOOP:
            case ATTACK:
                break;
            case UP:
                newY--;
                break;
            case DOWN:
                newY++;
                break;
            case LEFT:
                newX--;
                break;
            case RIGHT:
                newX++;
                break;
        }

        return Coordinate(newX, newY);
    }

    /**
     * Use this also!
     *
     * It calculates the difference between two coordinates.
     *
     * @param rhs Coordinate to calculate the difference.
     * @return The absolute distance (x + y) between them.
     */
    int operator-(const Coordinate& rhs) const {
        return abs(x - rhs.x) + abs(y - rhs.y);
    }
};

#endif //HW4_COORDINATE_H
