#ifndef HW3_TESTABLE_H
#define HW3_TESTABLE_H


#include <string>
#include <iostream>

#include <utility>
#include <cmath>

#include "Koin.h"
#include "Utilizer.h"

class Testable {
protected:
    int currentGrade;
    int maxGrade;
    std::string name;

    virtual void runInternal() = 0;
public:
    Testable(std::string name, int maxGrade) : name(std::move(name)), maxGrade(maxGrade), currentGrade(maxGrade) { }
    virtual ~Testable() = default;

    virtual bool isSuccessful() final {
        return this->currentGrade == this->maxGrade;
    }
    virtual int getFinalGrade() final {
        return this->currentGrade;
    }
    virtual int getMaxGrade() final {
        return this->maxGrade;
    }

    virtual void run() final {
        std::cout << this->name << " has started. (Max Grade: " << this->maxGrade << ")" << std::endl;

        runInternal();

        std::cout << this->name << " has finished. (Earned Grade: " << this->currentGrade << ")" << std::endl;
    }

    inline bool verifyKoinValues(Koin& koin1, Koin& koin2) {
        return verifyTwoValues(koin1.getValue(), koin2.getValue());
    }
    inline bool verifyKoinValue(Koin& koin, double value) {
        return verifyTwoValues(koin.getValue(), value);
    }
    inline bool verifyTwoValues(double value1, double value2) {
        return fabs(value1 - value2) <= Utilizer::doubleSensitivity();
    }
};


#endif //HW3_TESTABLE_H
