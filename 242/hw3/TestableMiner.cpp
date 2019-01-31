#include <sstream>
#include "TestableMiner.h"
#include "Miner.h"

void TestableMiner::runInternal() {

    // Phase 1 : Creating New Blockchain

    Miner btcMiner = Miner("BTCMiner");

    int blockchainToCreate = 5;

    for (int i = 0; i < blockchainToCreate; i++) {
        btcMiner.createNewBlockchain();
    }

    if (btcMiner.getBlockchainCount() != blockchainToCreate)
        currentGrade -= 2;

    // Phase 2 : Indexing

    for (int i = 0; i < blockchainToCreate; i++) {
        Blockchain *createdBlockchain = btcMiner[i];

        if (createdBlockchain == nullptr)
            currentGrade -= 1;
    }

    Blockchain *shouldBeNull = btcMiner[blockchainToCreate + 1];

    if (shouldBeNull != nullptr)
        currentGrade -= 2;

    // Phase 3 : Mine/Demine

    int mineCount = 100;
    int demineCount = 50;

    btcMiner.mineUntil(100);

    for (int i = 0; i < blockchainToCreate; i++) {
        Blockchain *blockchain = btcMiner[i];

        if (blockchain->getChainLength() != mineCount)
            currentGrade -= 2;
    }

    btcMiner.demineUntil(demineCount);

    for (int i = 0; i < blockchainToCreate; i++) {
        Blockchain *blockchain = btcMiner[i];

        if (blockchain->getChainLength() != (mineCount - demineCount))
            currentGrade -= 2;
    }

    // Phase 4 : Soft Fork

    Miner antMiner = Miner("ANTMiner");
    antMiner.createNewBlockchain();
    antMiner.mineUntil(10);
    /*
    -- BEGIN MINER --
    Miner name: ANTMiner
    Blockchain count: 1
    Total value: 5.926
    Block 0: 0.528--0.461--0.712--0.774--0.286--0.691--0.791--0.887--0.175--0.622--|(5.926)
    -- END MINER --
     */
    antMiner.softFork(0);
    /*
    -- BEGIN MINER --
    Miner name: ANTMiner
    Blockchain count: 2
    Total value: 5.926
    Block 0: 0.528--0.461--0.712--0.774--0.286--0.691--0.791--0.887--0.175--0.622--|(5.926)
    Block 1: 0.622--|(0.622)
    -- END MINER --
     */

    Blockchain *pureBlockchain = antMiner[0];
    Blockchain *softForkedBlockchain = antMiner[1];

    if (pureBlockchain == nullptr || softForkedBlockchain == nullptr) {
        currentGrade -= 4;
    }
    else {
        *softForkedBlockchain *= 2;
        /*
        -- BEGIN MINER --
        Miner name: ANTMiner
        Blockchain count: 2
        Total value: 6.548
        Block 0: 0.528--0.461--0.712--0.774--0.286--0.691--0.791--0.887--0.175--1.244--|(6.548)
        Block 1: 1.244--|(1.244)
        -- END MINER --
         */
        double pureBlockchainValue = 6.548;
        double softForkedBlockchainValue = 1.244;

        if (!verifyTwoValues(pureBlockchainValue, pureBlockchain->getTotalValue())
            || !verifyTwoValues(softForkedBlockchainValue, softForkedBlockchain->getTotalValue())) {
            currentGrade -= 2;
        }
    }

    // Phase 5 : Hard Fork

    Miner ethMiner = Miner("ETHMiner");
    ethMiner.createNewBlockchain(); // Pure blockchain
    ethMiner.mineUntil(1);

    int blockchainCountToCreate = 10;

    for(int i = 0; i < blockchainCountToCreate - 2; i++) {
        ethMiner.mineUntil(1);
        ethMiner.hardFork(i);
    }

    ethMiner.createNewBlockchain(); // Empty blockchain

    for(int i = 0; i < blockchainCountToCreate; i++) {
        Blockchain *currentBlockchain = ethMiner[i];

        if (currentBlockchain == nullptr) {
            currentGrade -= 1;
            continue;
        }

        // Block 0 should have 9 Koins.
        // Block 9 should have 0 Koin.
        // You can see the result in Stream Overload example below.
        int chainLength = (blockchainCountToCreate - 1 - i);

        if (currentBlockchain->getChainLength() != chainLength)
            currentGrade -= 1;
    }

    // Phase 5 : Stream Overload

    std::stringstream sstream;
    sstream << ethMiner;

    std::stringstream ethMinerResultStream;
    ethMinerResultStream
    << "-- BEGIN MINER --\n"
    << "Miner name: ETHMiner\n"
    << "Blockchain count: 10\n"
    << "Total value: 21.950\n"
    << "\n"
    << "Block 0: 0.940--0.029--0.241--0.905--0.402--0.401--0.197--0.447--0.989--|(4.549)\n"
    << "Block 1: 0.029--0.462--0.177--0.264--0.764--0.613--0.158--0.325--|(2.791)\n"
    << "Block 2: 0.462--0.330--0.345--0.705--0.271--0.429--0.412--|(2.954)\n"
    << "Block 3: 0.330--0.596--0.819--0.024--0.485--0.569--|(2.823)\n"
    << "Block 4: 0.596--0.531--0.335--0.452--0.500--|(2.414)\n"
    << "Block 5: 0.531--0.997--0.498--0.352--|(2.378)\n"
    << "Block 6: 0.997--0.950--0.819--|(2.766)\n"
    << "Block 7: 0.950--0.162--|(1.112)\n"
    << "Block 8: 0.162--|(0.162)\n"
    << "Block 9: Empty.\n"
    << "\n"
    << "-- END MINER --\n";

    if (ethMinerResultStream.str() != sstream.str())
        currentGrade -= 5;
}
