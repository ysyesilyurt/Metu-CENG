#ifndef HW4_TESTABLEBOARD_H
#define HW4_TESTABLEBOARD_H


#include "Testable.h"

class TestableBoard : public Testable {
private:
    void runInternal() override;
public:
    TestableBoard() : Testable("Board Test", 15) { }
};


#endif //HW4_TESTABLEBOARD_H
