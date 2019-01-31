#ifndef HW3_KOIN_H
#define HW3_KOIN_H

#include <ostream>

class Koin {

private:
    double value;

    Koin *next;

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PRIVATE METHODS/PROPERTIES BELOW
public:
    /**
     * Constructor.
     *
     * @param value The Koin's value.
     */
    Koin(double value);
    /**
     * Copy Constructor.
     *
     * @param rhs The koin to be copied.
     */
    Koin(const Koin& rhs);

    /**
     * Assignment.
     *
     * @param rhs The koin to assign into this koin.
     * @return The assigned koin.
     */
    Koin& operator=(const Koin& rhs);
    ~Koin();

    double getValue() const;

    Koin* getNext() const;
    /**
     * Sets the next chain for this Koin.
     *
     * Important: Koin does NOT "own" next.
     *
     * @param next The next Koin.
     */
    void setNext(Koin *next);

    /**
     * Equality overload.
     *
     * The Koins are equal if their values are equal, and their next Koins, and the next Koins' next koins... are also equal.
     *
     * Important: Since the values are double, you should refrain to use equality between two doubles.
     * Instead, they should be compared within a sensitivity, given in Utilities.h.
     *
     * @param rhs The Koin to compare.
     * @return True if they're equal, false otherwise.
     */
    bool operator==(const Koin& rhs) const;
    /**
     * Inequality overload.
     *
     * Explained in upper part.
     *
     * @param rhs The Koin to compare.
     * @return True if they're not equal, false otherwise.
     */
    bool operator!=(const Koin& rhs) const;

    /**
     * Multiply the value of the Koin with given multiplier.
     *
     * @param multiplier The value to multiply the Koin's value.
     * @return The current Koin.
     */
    Koin& operator*=(int multiplier);
    /**
     * Divide the value of the Koin with given divisor.
     *
     * @param divisor The value to divide the Koin's value.
     * @return The current Koin.
     */
    Koin& operator/=(int divisor);

    /**
     * Stream overload.
     *
     * What to stream:
     * koinValue--nextKoin's value--nextKoins' nextKoin's value--...--| (pipe at the end)
     *
     * Example:
     * 0.439--0.439--0.439--|
     *
     * Important: The precision required is given to you in Utilizer.h.
     * For this example, it's 3.
     *
     * @param os Stream to be used.
     * @param koin Koin to be streamed.
     * @return The current Stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Koin& koin);

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW

    void setValue(double value);

};


#endif //HW3_KOIN_H
