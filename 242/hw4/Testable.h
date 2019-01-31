#ifndef HW4_TESTABLE_H
#define HW4_TESTABLE_H

#include <string>
#include <iostream>

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

};


#endif //HW4_TESTABLE_H
