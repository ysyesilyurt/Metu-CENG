#include <vector>

#include "TestableKoin.h"
#include "TestableBlockchain.h"
#include "TestableMiner.h"
#include "TestableAllStream.h"

enum Test {
    KOIN,
    BLOCKCHAIN,
    MINER,
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
std::pair<int, int> createAndRunTest(Test testType) {

    Testable* testToRun = nullptr;

    switch(testType) {
        case KOIN:
            testToRun = new TestableKoin();
            break;
        case BLOCKCHAIN:
            testToRun = new TestableBlockchain();
            break;
        case MINER:
            testToRun = new TestableMiner();
            break;
        case ALLSTREAM:
            testToRun = new TestableAllStream();
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

    std::vector<Test> testToRun = { KOIN, BLOCKCHAIN, MINER, ALLSTREAM };
    //std::vector<Test> testToRun = { ALLSTREAM };
    //std::vector<Test> testToRun = { KOIN , BLOCKCHAIN, MINER};

    for (auto test : testToRun) {
        std::pair<int, int> testResult = createAndRunTest(test);

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
    std::cout << "Memory Test: 20 (5 for each test)" << std::endl;
    std::cout << "Output Test: 35" << std::endl;

    return 0;
}