#ifndef HW4_TESTABLEGAMEPARSER_H
#define HW4_TESTABLEGAMEPARSER_H


#include "Testable.h"

class TestableGameParser : public Testable {
private:
    const std::string filenameToTest;

    void runInternal() override;
public:
    TestableGameParser(const std::string& filename) : Testable("Game Parser Test", 5), filenameToTest(filename) { }
};


#endif //HW4_TESTABLEGAMEPARSER_H
