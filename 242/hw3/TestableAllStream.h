
#ifndef HW3_TESTABLEALLSTREAM_H
#define HW3_TESTABLEALLSTREAM_H


#include "Testable.h"

class TestableAllStream : public Testable {
private:
    void runInternal() override;

public:
    TestableAllStream() : Testable("All Stream Test", 0) { }
};


#endif //HW3_TESTABLEALLSTREAM_H
