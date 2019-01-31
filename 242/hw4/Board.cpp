#include "Board.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Board::Board(uint boardSizee, std::vector<Player *> *playerss) : boardSize(boardSizee) , players(playerss) , stormSize(0)
{

}

Board::~Board() = default;

uint Board::getSize() const
{
    return boardSize;
}

bool Board::isCoordInBoard(const Coordinate &coord) const
{
    return (((coord.x >= 0) && (coord.x <= boardSize - 1)) && ((coord.y >= 0) && (coord.y <= boardSize - 1)));
}

bool Board::isStormInCoord(const Coordinate &coord) const
{
    if(!isCoordInBoard(coord))
        return false;
    else // left right up down check at every || check changes
        return ((coord.x < stormSize) || ((coord.x < boardSize) && coord.x > boardSize - stormSize - 1) || (coord.y < stormSize) || ((coord.y < boardSize) && coord.y > boardSize - stormSize - 1));
}

bool Board::isCoordHill(const Coordinate &coord) const //  Board size will be n > 2; n < 28; n%2 == 1
{
    return ((coord.x == ((boardSize - 1) / 2)) && (coord.y == ((boardSize - 1) / 2)));
}

Player* Board::operator[](const Coordinate &coord) const
{
    if(!isCoordInBoard(coord))
        return nullptr;
    else
    {
        for (int i = 0; i < players->size(); ++i) {
            if(coord == (*players)[i]->getCoord())
                return (*players)[i];
        }
        return nullptr;
    }
}

Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const
{
    if(move == NOOP || move == ATTACK)
        return coord;
    else
    {
        Coordinate newCoord(coord + move);
        if(!isCoordInBoard(newCoord))
            return coord;
        else
        {
            for (int i = 0; i < players->size(); ++i) {
                if(newCoord == (*players)[i]->getCoord())
                    return coord;
            }
            return newCoord;
        }
    }
}

std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const
{
    std::vector<Coordinate> returnVector;
    if(!isCoordInBoard(coord))
        return returnVector;
    else
    {
        if(isCoordInBoard(coord + UP))
        {
            Coordinate x = coord + UP;
            returnVector.emplace_back(x);
        }
        if(isCoordInBoard(coord + DOWN))
        {
            Coordinate x = coord + DOWN;
            returnVector.emplace_back(x);
        }
        if(isCoordInBoard(coord + LEFT))
        {
            Coordinate x = coord + LEFT;
            returnVector.emplace_back(x);
        }
        if(isCoordInBoard(coord + RIGHT))
        {
            Coordinate x = coord + RIGHT;
            returnVector.emplace_back(x);
        }    }
}

void Board::updateStorm(uint currentRound)
{
    if(stormSize == ((boardSize - 1) / 2))
        return;
    else if (currentRound == 0)
        return;
    else
        stormSize = Entity::stormWidthForRound(currentRound);
}


Coordinate Board::getHillCoord() const
{
    Coordinate x(((boardSize - 1) / 2),((boardSize - 1) / 2));
    return x;
}