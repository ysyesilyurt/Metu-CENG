#ifndef HW4_GAMEPARSER_H
#define HW4_GAMEPARSER_H

#include <vector>
#include "Player.h"

class GameParser {
public:
    /**
     * Parse the file with given name and create players accordingly.
     *
     * GameParser DOES NOT have any responsibility over these Players.
     *
     * Note: The file will always exists, and there will be no erroneous input.
     *
     * @param filename The name of the file to be parsed.
     * @return  pair.first: Board size.
     *          pair.second: The vector of the constructed players.
     */
    static std::pair<int, std::vector<Player *> *> parseFileWithName(const std::string& filename);
};


#endif //HW4_GAMEPARSER_H
