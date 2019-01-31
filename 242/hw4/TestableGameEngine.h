#ifndef HW4_TESTABLEGAMEENGINE_H
#define HW4_TESTABLEGAMEENGINE_H


#include "Testable.h"

class TestableGameEngine : public Testable {
private:
    void runInternal() override;
public:
    TestableGameEngine() : Testable("Game Engine Test", 25) { }
};


#endif //HW4_TESTABLEGAMEENGINE_H
