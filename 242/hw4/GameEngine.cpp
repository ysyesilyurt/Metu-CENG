#include <iostream>
#include "GameEngine.h"
#include <algorithm>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players) : board(boardSize,players) , currentRound(0) , playerVector(players)
{
    std::sort((*playerVector).begin(),(*playerVector).end(),Player::comparePlayers);
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < playerVector->size(); ++i) {
        delete (*playerVector)[i];
    }
    playerVector->clear(); // does nothing
    delete playerVector; // delete [] playerVector ???
}

const Board& GameEngine::getBoard() const
{
    return board;
}

Player* GameEngine::operator[](uint id) const
{
    for (int i = 0; i < playerVector->size(); ++i) {
        if((*playerVector)[i]->getID() == id)
            return (*playerVector)[i];
    }
    return nullptr;
}

bool GameEngine::isFinished() const // (*board.getPlayers())[0] <= sola kaydirip sagdan nullifying and keep index consistent
{
    if(playerVector->empty())
        return true;
    else
        return ((playerVector->size() == 1) && (board.isCoordHill((*playerVector)[0]->getCoord())));
}

void GameEngine::takeTurn()
{
    currentRound++;
    std::cout << "-- START ROUND " << currentRound << " --\n";
    board.updateStorm(currentRound);

    for (int i = 0; i < playerVector->size(); ++i) {
        anybodyDied = false;
        takeTurnForPlayer((*playerVector)[i]->getID());
        if(anybodyDied)
        {
            if(!diedFromWhere) // died from left or died itself! Do not shift i!
                i--;
            else // died from right! Np carry on!
                continue;
        }
    }
    std::cout << "-- END ROUND " << currentRound << " --\n";
}

Move GameEngine::takeTurnForPlayer(uint playerID)
{
    if(!this->operator[](playerID))
        return NOOP;

    std::vector<Move> playersPrioritylist = this->operator[](playerID)->getPriorityList();
    std::vector<Coordinate> playersVisibility = board.visibleCoordsFromCoord(this->operator[](playerID)->getCoord());

    if(board.isStormInCoord(this->operator[](playerID)->getCoord()))
    {
        std::cout << this->operator[](playerID)->getFullName() + "("+ std::to_string(this->operator[](playerID)->getHP()) + ")";
        std::cout << " is STORMED! (-" << Entity::stormDamageForRound(currentRound) << ")\n";
        this->operator[](playerID)->setHP(this->operator[](playerID)->getHP() - Entity::stormDamageForRound(currentRound));
    }

    if(this->operator[](playerID)->isDead())
    {
        std::cout << this->operator[](playerID)->getFullName() + "("+ std::to_string(this->operator[](playerID)->getHP()) + ")" << " DIED.\n";

        int index = 0;
        for (int i = 0; i < playerVector->size(); ++i) {
            if((*playerVector)[i]->getID() == playerID)
                break;
            index++;
        }
        delete this->operator[](playerID);
        (*playerVector).erase(playerVector->begin() + index); // erases and shifts in vector

        anybodyDied = true;
        diedFromWhere = false; // do not shift i!

        return NOOP;
    }

    for (int i = 0; i < playersPrioritylist.size(); ++i) {

        if(playersPrioritylist[i] == NOOP)
            return NOOP;

        else if(playersPrioritylist[i] == ATTACK)
        {
            std::vector<uint> playerIdInSight;

            for (int j = 0; j < playersVisibility.size(); ++j) {
                if(board[playersVisibility[j]])
                {
                    int playerId = board[playersVisibility[j]]->getID();
                    playerIdInSight.emplace_back(playerId); // store the player id's into that vector
                }
            }

            if(!playerIdInSight.empty()) // there is somebody to attack to!
            {
                int minIndex = 0;
                for (int j = 0; j < playerIdInSight.size(); ++j) {
                    if(playerIdInSight[minIndex] > playerIdInSight[j])
                        minIndex = j;
                }

                bool isPlayerDead = this->operator[](playerID)->attackTo(this->operator[](playerIdInSight[minIndex]));

                if(isPlayerDead)
                {
                    std::cout << this->operator[](playerIdInSight[minIndex])->getFullName() + "("+ std::to_string(this->operator[](playerIdInSight[minIndex])->getHP()) + ")" << " DIED.\n";

                    int index = 0;
                    for (int j = 0; j < playerVector->size(); ++j) {
                        if((*playerVector)[j]->getID() == this->operator[](playerIdInSight[minIndex])->getID())
                            break;
                        index++;
                    }

                    anybodyDied = true;
                    diedFromWhere = (this->operator[](playerID)->getID() < playerIdInSight[minIndex]); // left or right!

                    delete this->operator[](playerIdInSight[minIndex]);
                    (*playerVector).erase(playerVector->begin() + index); // erases and shifts in vector

                    return ATTACK;
                }
                return ATTACK;
            }
            else // ATTACK move fails (nobody to attack to!), continue!
                continue;
        }

        else // UP/DOWN/LEFT/RIGHT
        {
            Coordinate newCoord = board.calculateCoordWithMove(playersPrioritylist[i],this->operator[](playerID)->getCoord());

            if((newCoord != this->operator[](playerID)->getCoord()) && ((newCoord - board.getHillCoord()) < (this->operator[](playerID)->getCoord()) - board.getHillCoord()))
            {
                this->operator[](playerID)->executeMove(playersPrioritylist[i]);
                return playersPrioritylist[i];
            }
            else // UP/DOWN/LEFT/RIGHT move fails , continue
                continue;
        }
    }
    return NOOP;
}

Player* GameEngine::getWinnerPlayer() const
{
    if(isFinished())
    {
        if(playerVector->size() == 1)
            return (*playerVector)[0];
        else
            return nullptr;
    }

    else
        return nullptr;
}