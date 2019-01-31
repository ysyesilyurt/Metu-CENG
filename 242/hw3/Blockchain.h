#ifndef HW3_BLOCKCHAIN_H
#define HW3_BLOCKCHAIN_H

#include "Koin.h"

#include <ostream>

class Blockchain {

private:
    Koin *head;

    const int id;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PRIVATE METHODS/PROPERTIES BELOW

public:
    /**
     * Constructor.
     *
     * @param id The ID of the Blockchain.
     */
    Blockchain(int id);
    /**
     * Secondary Constructor.
     *
     * Important: Blockchain "owns" this Koin.
     *
     * @param id The ID of the Blockchain.
     * @param head The starting point of the Blockchain.
     */
    Blockchain(int id, Koin *head);
    /**
     * Copy Constructor.
     *
     * The head should be deep copied.
     *
     * @param rhs The blockchain to be copied.
     */
    Blockchain(const Blockchain& rhs);
    /**
     * Move Operator.
     *
     * RHS will relinquish the rights of the headKoin to LHS.
     * LHS's ID will not (cannot) be changed.
     *
     * Careful about memory-leaks!
     *
     * @param rhs The blockchain to be moved into this blockchain.
     * @return The modified blockchain.
     */
    Blockchain& operator=(Blockchain&& rhs) noexcept;
    /**
     * No assignment with const rhs.
     *
     * @param rhs -noNeed-
     * @return -noNeed-
     */
    Blockchain& operator=(const Blockchain& rhs) = delete;
    ~Blockchain();

    int getID() const;
    Koin* getHead() const;

    /**
     * Calculate the value of the blockchain.
     *
     * @return Total value of the Koins in the blockchain.
     */
    double getTotalValue() const;

    /**
     * Calculate the length of the koins end-to-end.
     *
     * @return The length of the blockchain.
     */
    long getChainLength() const;

    /**
     * Prefix addition.
     *
     * Mine and insert the mined Koin at the end of the chain.
     */
    void operator++();

    /**
     * Prefix decrement.
     *
     * Remove/destroy the last inserted Koin to the chain.
     * no-op if the head is nullptr.
     *
     * Important note:
     *
     * If a blockchain is created by a soft fork, its head cannot be deleted.!!!!!
     */
    void operator--();

    /**
     * Multiplication overload.
     *
     * Multiply the value of every Koin in the blockchain.
     *
     * @param multiplier The value to be multiplied with the values of the Koins.
     * @return The current blockchain.
     */
    Blockchain& operator*=(int multiplier);

    /**
     * Division.
     *
     * Divide the value of every Koin in the blockchain.
     *
     * @param divisor The value to divide the values of the Koins.
     * @return The current blockchain.
     */
    Blockchain& operator/=(int divisor);

    /**
     * Stream overload.
     *
     * What to stream:
     *
     * Block -blockchainID-: headKoinStream (see Koin for stream example) (-totalValue-)
     *
     * Example:
     *
     * Block 6: 0.707--0.390--0.984--|(2.080)
     *
     * Edge case : Blockchain without head
     *
     * Block -blockchainID-: Empty.
     *
     * @param os Stream to be used.
     * @param blockchain Blockchain to be streamed.
     * @return The current stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain);
    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW

    bool isSoft = false;

};


#endif //HW3_BLOCKCHAIN_H
