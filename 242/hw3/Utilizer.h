#ifndef HW3_UTILIZER_H
#define HW3_UTILIZER_H

#include "randomc.h"

// engin:
// Use this class as-is.
// Do not forget to seed if you want to produce the same results for testing.
//
// You don't need to change the randomSeed, but for testing purposes you may.
//
// Usage For Koins:
// float newKoinValue = Utilizer::fetchRandomValue()
//
// Koin newKoin = Koin(newKoinValue);

// DO NOT MODIFY THIS FILE.
// THIS FILE WILL BE PROVIDED WITH DIFFERENT RANDOMSEED/SENSITIVITY/PRINTPRECISION IN GRADING.

class Utilizer {
private:
    const static int randomSeed = 1992;

    CRandomMersenne rng;

    Utilizer(int randomSeed) : rng(CRandomMersenne(randomSeed)) { }

    static Utilizer& getInstance()
    {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        static Utilizer instance(randomSeed);

        return instance;
    }

public:
    inline static double fetchRandomValue() {
        return getInstance().rng.Random();
    }

    inline static double doubleSensitivity() {
        return 0.001;
    }

    inline static int koinPrintPrecision() {
        return 3; // (%0.3f)
    }
};


#endif //HW3_UTILIZER_H