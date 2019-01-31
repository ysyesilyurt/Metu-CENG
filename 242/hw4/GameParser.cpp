#include "GameParser.h"
#include "Berserk.h"
#include "Tracer.h"
#include "Pacifist.h"
#include "Dummy.h"
#include "Ambusher.h"
#include <fstream>
#include <sstream>
#include <iostream>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string &filename) // second * refers to 'ptr to that vector'
{
    std::ifstream fileStream(filename);
    std::string line,tempForBoard;

    std::getline(fileStream,line); // Board Size: 3
    tempForBoard = line.substr(line.find(':') + 2,line.length());
    std::getline(fileStream,line); // Player Count: 2
    line = line.substr(line.find(':') + 2,line.length());
    int playerCount = std::stoi(line);

    std::pair<int, std::vector<Player *> *> returnPair;

    returnPair.first = std::stoi(tempForBoard);

    std::vector<Player *> * playerVector = new std::vector<Player *>;

    std::string playerType, playerId, playerX, playerY, temp;

    for (int i = 0; i < playerCount; ++i)
    {
        std::getline(fileStream,line);
        std::stringstream delimizer(line);

        std::getline(delimizer, playerId, ':');
        std::getline(delimizer, temp, ':'); // second ':'
        std::getline(delimizer, playerType, ':');
        std::getline(delimizer, temp, ':'); // second ':'
        std::getline(delimizer, playerX, ':');
        std::getline(delimizer, temp, ':'); // second ':'
        std::getline(delimizer, playerY);

        if(playerType == "Berserk")
        {
            uint id = (uint)std::stoi(playerId);
            int x = std::stoi(playerX);
            int y = std::stoi(playerY);

            playerVector->emplace_back(new Berserk(id,x,y));
        }
        else if(playerType == "Tracer")
        {
            uint id = (uint)std::stoi(playerId);
            int x = std::stoi(playerX);
            int y = std::stoi(playerY);
            playerVector->emplace_back(new Tracer(id,x,y));
        }
        else if(playerType == "Ambusher")
        {
            uint id = (uint)std::stoi(playerId);
            int x = std::stoi(playerX);
            int y = std::stoi(playerY);
            playerVector->emplace_back(new Ambusher(id,x,y));
        }
        else if(playerType == "Dummy")
        {
            uint id = (uint)std::stoi(playerId);
            int x = std::stoi(playerX);
            int y = std::stoi(playerY);
            playerVector->emplace_back(new Dummy(id,x,y));
        }
        else if(playerType == "Pacifist")
        {
            uint id = (uint)std::stoi(playerId);
            int x = std::stoi(playerX);
            int y = std::stoi(playerY);
            playerVector->emplace_back(new Pacifist(id,x,y));
        }
    }

    returnPair.second = playerVector;

    return returnPair;
}