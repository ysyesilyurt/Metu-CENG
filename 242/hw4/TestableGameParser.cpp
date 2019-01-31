#include "TestableGameParser.h"

#include "GameParser.h"

void TestableGameParser::runInternal() {
    // Phase 1: Parse the given file.

    /**
     * Board Size: 3
     * Player Count: 2
     * 0::Tracer::2::0
     * 1::Berserk::2::2
     */

    /**
     * It should boil down to:
     *
     * Tracer(0, 2, 0)
     * Berserk(1, 2, 2)
     */

    auto parsedValues = GameParser::parseFileWithName(this->filenameToTest);

    if(parsedValues.first != 3)
        currentGrade -= 2;

    std::vector<Player *> *players = parsedValues.second;

    if(players->size() != 2)
        currentGrade -= 2;

    // Removing memory manually...
    // Normally GameEngine will/should do this.

    for(Player *player : *players) {
        delete player;
    }

    players->clear();
    delete players;
}
