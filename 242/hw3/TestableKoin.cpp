#include <iostream>
#include <sstream>

#include "TestableKoin.h"

void TestableKoin::runInternal() {
    double randVal = Utilizer::fetchRandomValue();

    // Phase 1 : Constructor

    Koin koin1(randVal);
    Koin koin2(randVal);

    if (!verifyKoinValue(koin1, randVal))
        currentGrade -= 1;
    if (!verifyKoinValue(koin2, randVal))
        currentGrade -= 1;

    // Phase 2 : Copy Constructor

    Koin koin3(koin1);

    if (!verifyKoinValues(koin3, koin1))
        currentGrade -= 1;

    // Phase 3 : Assignment

    Koin koinToAssign(0.1);
    Koin koinToAssignChain(0.2);
    koinToAssign.setNext(&koinToAssignChain);

    Koin koinAssigned(0.0);
    Koin koinAssignedChain(0.333);
    koinAssigned.setNext(&koinAssignedChain);

    koinAssigned = koinToAssign;

    if (!verifyKoinValues(koinAssigned, koinToAssign))
        currentGrade -=1;
    if (!verifyKoinValues(*koinAssigned.getNext(), *koinToAssign.getNext()))
        currentGrade -= 1;

    // Phase 4 : Equality

    if (koin1 != koin2 || koin2 != koin3 || koin1 != koin3)
        currentGrade -= 2;

    koin1.setNext(&koin2);
    koin2.setNext(&koin3);

    if (koin1 == koin2 || koin2 == koin3 || koin1 == koin3)
        currentGrade -= 2;

    // Phase 5 : Equality + Copy Const

    Koin koin4(koin2);
    Koin koin5(randVal);

    koin3.setNext(&koin5);

    if (koin2 != koin4)
        currentGrade -= 2;

    // Phase 6 : Multiply/Divide

    std::stringstream sstream;
    sstream << koin1.getValue();
    koin1 *= 5;
    sstream << " " << koin1.getValue();
    koin1 /= 10;
    sstream << " " << koin1.getValue();

    std::string koin1MulDivResult = "0.438945 2.19472 0.219472";

    if (koin1MulDivResult != sstream.str())
        currentGrade -= 3;

    // Phase 6 : Stream Overload

    sstream.str(std::string()); // Clear the stream
    sstream << koin1;

    std::string koin1OverloadResult = "0.219--0.439--0.439--0.439--|";
    if (koin1OverloadResult != sstream.str())
        currentGrade -= 3;
}