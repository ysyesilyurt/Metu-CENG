#include "TestableAllStream.h"
#include "Miner.h"

void TestableAllStream::runInternal() {
    // Note: These cout's will be redirected to a file and compared line-by-line.
    // Hence, the immediate/max grade is 0.

    // Phase 1:

    Miner btcMiner("BTCMiner");

    long blockchainsToCreate = 10;

    for(int i = 0; i < blockchainsToCreate; i++) {
        btcMiner.createNewBlockchain();
        btcMiner.mineUntil(2);
        btcMiner.demineUntil(1);
    }

    std::cout << btcMiner << std::endl;

    for(int i = 0; i < blockchainsToCreate; i++) {
        (*btcMiner[i]) *= 10;
        btcMiner.hardFork(i);
    }

    std::cout << btcMiner << std::endl;

    for(int i = 0; i < blockchainsToCreate * 2; i++) {
        btcMiner.mineUntil(1);
        btcMiner.softFork(i);
    }

    std::cout << btcMiner << std::endl;

    // Phase 2:

    Miner ethMiner("ETHMiner");

    for(int i = 0; i < blockchainsToCreate; i++) {
        ethMiner.createNewBlockchain();
        ethMiner.mineUntil(1);
    }

    for(int i = 0; i < blockchainsToCreate; i++) {
        ethMiner.softFork(i);
    }

    std::cout << ethMiner << std::endl;

    ethMiner.demineUntil(1000000);

    std::cout << ethMiner << std::endl;
}