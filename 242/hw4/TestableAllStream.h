#ifndef HW4_TESTABLEALLSTREAM_H
#define HW4_TESTABLEALLSTREAM_H


#include "Testable.h"

class TestableAllStream : public Testable {
private:
    const std::string filenameToTest;

    void runInternal() override;
public:
    TestableAllStream(const std::string& filename) : Testable("All Stream Test", 0), filenameToTest(filename) { }
};


#endif //HW4_TESTABLEALLSTREAM_H
