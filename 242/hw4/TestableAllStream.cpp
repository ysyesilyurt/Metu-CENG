#include "TestableAllStream.h"
#include "GameParser.h"
#include "GameEngine.h"
#include "BoardPrinter.h"

void TestableAllStream::runInternal() {
    // Note: These cout's will be redirected to a file and compared line-by-line.
    // Hence, the immediate/max grade is 0.

    auto parserResult = GameParser::parseFileWithName(this->filenameToTest);

    GameEngine engine = GameEngine(parserResult.first, parserResult.second);

    BoardPrinter::printBoard(engine.getBoard());

    int infiniteLoopDisengage = 0;

    while(!engine.isFinished()) {
        if(++infiniteLoopDisengage > 500) {
            // To prevent infinite loop.
            break;
        }

        engine.takeTurn();

        BoardPrinter::printBoard(engine.getBoard());
    }

    Player *chickenDinner = engine.getWinnerPlayer();

    // Spoiler alert: Tracer00 wins.
    if (chickenDinner == nullptr) {
        currentGrade -= 5;
    }
    else {
        std::cout << chickenDinner->getFullName() << " won!!!" << std::endl;
    }

    std::cout << std::endl;
}
