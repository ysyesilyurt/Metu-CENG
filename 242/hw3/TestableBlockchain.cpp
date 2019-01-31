#include <sstream>
#include "TestableBlockchain.h"
#include "Blockchain.h"

void TestableBlockchain::runInternal() {

    // Phase 1 : Constructor

    Blockchain blockchain1(1);
    Blockchain blockchain2(2);

    Koin *head1 = blockchain1.getHead();
    Koin *head2 = blockchain2.getHead();

    if (blockchain1.getID() != 1 || blockchain2.getID() != 2 || head1 != nullptr || head2 != nullptr)
        currentGrade -= 1;

    Koin *head3 = new Koin(0.5);

    Blockchain blockchain3(3, head3);

    Koin *actualHead3 = blockchain3.getHead();

    if (head3 == nullptr || !verifyKoinValues(*head3, *actualHead3))
        currentGrade -= 1;

    // Phase 2 : Copy Constructor

    Blockchain blockchain4(blockchain3);

    Koin *head4 = blockchain4.getHead();

    if (head3 == nullptr || !verifyKoinValues(*head4, *actualHead3))
        currentGrade -= 2;

    // Phase 3 : Move

    Blockchain blockchain5(blockchain4);

    blockchain5 = std::move(blockchain3);

    // Phase 4 : Operations

    int koinCount = 10;

    for(int i = 0; i < koinCount; i++) {
        ++blockchain1;
    }

    double actualValue = 6.0434;

    if (!verifyTwoValues(actualValue, blockchain1.getTotalValue()))
        currentGrade -= 1;

    blockchain1 *= 10;

    if (!verifyTwoValues(actualValue * 10, blockchain1.getTotalValue()))
        currentGrade -= 1;

    blockchain1 /= 10;

    if (!verifyTwoValues(actualValue, blockchain1.getTotalValue()))
        currentGrade -= 1;

    long chainLength = blockchain1.getChainLength();

    if (chainLength != koinCount)
        currentGrade -= 1;

    for(int i = 0; i < 100; i++) {
        --blockchain1;
    }

    if (!verifyTwoValues(0, blockchain1.getTotalValue()))
        currentGrade -= 1;

    chainLength = blockchain1.getChainLength();

    if (chainLength != 0)
        currentGrade -= 1;

    // Phase 5 : Stream Overload

    for(int i = 0; i < 5; i++) {
        ++blockchain2;
    }

    std::stringstream sstream;
    sstream << blockchain1;

    std::string blockchain1Result = "Block 1: Empty.";

    if (blockchain1Result != sstream.str())
        currentGrade -= 2;

    sstream.str(std::string()); // Clear the stream
    sstream << blockchain2;
    std::string hey = sstream.str();
    std::string blockchain2Result = "Block 2: 0.965--0.047--0.532--0.385--0.883--|(2.811)";

    if (blockchain2Result != sstream.str())
        currentGrade -= 2;
}
