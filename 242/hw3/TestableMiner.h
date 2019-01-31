#ifndef HW3_TESTABLEMINER_H
#define HW3_TESTABLEMINER_H


#include "Testable.h"

class TestableMiner : public Testable {
private:
    void runInternal() override;
public:
    TestableMiner() : Testable("Miner Test", 20) { }
};


#endif //HW3_TESTABLEMINER_H
