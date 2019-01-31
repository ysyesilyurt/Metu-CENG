#include <iostream>

#include "Testable.h"
#include "TestablePlayer.h"
#include "TestableBoard.h"
#include "TestableGameEngine.h"
#include "TestableGameParser.h"
#include "TestableAllStream.h"

enum Test {
    PLAYER,
    PARSER,
    BOARD,
    ENGINE,
    ALLSTREAM
};

/**
 * Start testing for given type.
 *
 * Every test will have +[0-5] points with the valgrind test.
 *
 * @param testType The test type to run.
 * @return pair.first  : Earned grade
 *         pair.second : Max grade
 */
std::pair<int, int> createAndRunTest(Test testType, const std::string& inputFileName = "") {

    Testable* testToRun = nullptr;

    switch(testType) {
        case PLAYER:
            testToRun = new TestablePlayer();
            break;
        case PARSER:
            testToRun = new TestableGameParser(inputFileName);
            break;
        case BOARD:
            testToRun = new TestableBoard();
            break;
        case ENGINE:
            testToRun = new TestableGameEngine();
            break;
        case ALLSTREAM:
            testToRun = new TestableAllStream(inputFileName);
            break;
    }

    testToRun->run();

    int grade = testToRun->getFinalGrade();
    int maxGrade = testToRun->getMaxGrade();

    delete testToRun;

    return std::make_pair(grade, maxGrade);
}

int main(int argc, char** argv) {
    int totalGrade = 0;
    int maxGrade = 0;

    std::vector<Test> testToRun = { PLAYER, BOARD, ENGINE, PARSER , ALLSTREAM};
    // testToRun = { };

    if(argc != 1) {
        // Input file is given. Go for TestableGameParser!
        testToRun.push_back(PARSER);

        // Also you may want to test it all.
        testToRun.push_back(ALLSTREAM);
    }

    for (auto test : testToRun) {
        std::pair<int, int> testResult = (test == PARSER || test == ALLSTREAM) ? createAndRunTest(test, argv[1]) : createAndRunTest(test);

        totalGrade += testResult.first;
        maxGrade += testResult.second;
    }

    // engin: This will not be printed while checking for the output matching.

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Total partial grade: " << totalGrade << "/" << maxGrade << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    std::cout << "Reserved grades:" << std::endl;
    std::cout << "Memory Test: 20" << std::endl;
    std::cout << "Output Test: 20" << std::endl;

    return 0;
}