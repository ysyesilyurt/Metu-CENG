#ifndef HW3_MINER_H
#define HW3_MINER_H

#include "Blockchain.h"

#include <ostream>
#include <vector>

class Miner {

private:
    /**
     * Find the next ID for a newly created/forked blockchain.
     * Blockchain IDs are unique belonging to Miner, and strictly increasing (started from 0).
     *
     * @return The next available ID for a new blockchain.
     */
    int getNextAvailableBlockchainID() const;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PRIVATE METHODS/PROPERTIES BELOW

    int last_blockchainID;
    std::string name;
    std::vector< std::pair<Blockchain *,bool> > minerChain;
    std::vector< std::pair<int,double> > softforkedChains;

public:
    /**
     * Constructor.
     *
     * @param name Name of the miner.
     */
    Miner(std::string name);
    ~Miner();

    /**
     * Create a new blockchain with the next available ID.
     */
    void createNewBlockchain();

    /**
     * Start mining with the given count.
     * For every count, a single Koin will be produced in each blockchain.
     *
     * Operations must be ordered according to the blockchainIDs.
     *
     * @param cycleCount The count which the blockchains will be run for.
     */
    void mineUntil(int cycleCount);

    /**
     * Start de-mining with the given count.
     * For every count, the last Koin in the blockchain must be destroyed.
     * no-op for Blockchain if it doesn't have any (left).
     *
     * Operations must be ordered according to the blockchainIDs.
     *
     * @param cycleCount The count which the blockchains will be run for.
     */
    void demineUntil(int cycleCount);

    /**
     * Calculate the value of the miner, which is the sum of the blockchains' value.
     *
     * Soft-forks DO NOT constitute for the total value of the miner.
     *
     * @return Total value of the miner.
     */
    double getTotalValue() const;

    /**
     * Return the count of the blockchains.
     *
     * @return Total count of the blockchains.
     */
    long getBlockchainCount() const;

    /**
     * Indexing.
     *
     * Find the blockchain with the given id.
     *
     * @return The blockchain with the given id. nullptr if not exists.
     */
    Blockchain* operator[](int id) const;

    /**
     *  Shallow-copy the blockchain with given ID.
     *
     *  How-To:
     *  1) Fetch the blockchain in the miner with given ID.
     *  2) If not exists, no-op.
     *  3) Fetch the next available ID for the blockchain.
     *  4) Create a new blockchain with the new ID, and with the head as the original of the last Koin of the blockchain.
     *  5) Hence, a modification to the newly created blockchain will also affect the old blockchain, but only ...
     *  6) ... after the head (head included). And vice versa.
     *  7) Save the newly created blockchain in the miner.
     *
     *  @param blockchainID The blockchain ID to be forked.
     *
     *  @return true if the blockchain with given ID exists, otherwise false.
    */
    bool softFork(int blockchainID);

    /**
     *  Deep-copy the blockchain with given ID.
     *
     *  How-To:
     *  1) Fetch the blockchain in the miner with given ID.
     *  2) If not exists, no-op.
     *  3) Else, fetch the next available ID for the blockchain.
     *  4) Create a new blockchain with the new ID, and with the head as a copy of the last Koin of the blockchain.
     *  5) Any changes made in the new blockchain will NOT affect the old blockchain. And vice versa.
     *  6) Save the newly created blockchain in the miner.
     *
     *  @param blockchainID The blockchain ID to be forked.
     *
     *  @return true if the blockchain with given ID exists, otherwise false.
    */
    bool hardFork(int blockchainID);

    /**
     * Stream overload.
     *
     * What to stream:
     *
     * -- BEGIN MINER --
     * Miner name: -minerName-
     * Blockchain count: -getBlockchainCount()-
     * Total value: -getTotalValue()-
     *
     * Block -blockchainID-: headKoin (see Blockchain for stream example)
     * .
     * .
     * .
     * Block -lastBlockchainID-: headKoin (see Blockchain for stream example)
     *
     * -- END MINER --
     *
     * Example:
     *
     * -- BEGIN MINER --
     * Miner name: BTCMiner
     * Blockchain count: 5
     * Total value: 2.519
     *
     * Block 0: 0.491--0.103--0.529--|(1.123)
     * Block 1: Empty.
     * Block 2: Empty.
     * Block 3: Empty.
     * Block 4: 0.400--0.924--0.072--|(1.396)
     *
     * -- END MINER --
     *
     * @param os Stream to be used.
     * @param miner Miner to be streamed.
     * @return The current stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Miner& miner);

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW

    std::vector< std::pair<Blockchain *,bool> > getChain() const;


};


#endif //HW3_MINER_H
