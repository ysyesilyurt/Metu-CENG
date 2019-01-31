#ifndef HW3_TESTABLEKOIN_H
#define HW3_TESTABLEKOIN_H


#include "Testable.h"

class TestableKoin : public Testable {
private:
    void runInternal() override;
public:
    TestableKoin() : Testable("Koin Test", 10) { }
};


#endif //HW3_TESTABLEKOIN_H
