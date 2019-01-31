#ifndef HW3_TESTABLEBLOCKCHAIN_H
#define HW3_TESTABLEBLOCKCHAIN_H


#include "Testable.h"

class TestableBlockchain : public Testable {
private:
    void runInternal() override;

public:
    TestableBlockchain() : Testable("Blockchain Test", 15) { }
};


#endif //HW3_TESTABLEBLOCKCHAIN_H
