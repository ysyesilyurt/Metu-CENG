#include <iomanip>
#include "Koin.h"
#include "Utilizer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Koin::Koin(double value)
{
    Koin::value = value;
    next = nullptr;
}

Koin::Koin(const Koin &rhs)
{
    *this = rhs;
}

Koin& Koin::operator=(const Koin &rhs)
{
    value = rhs.getValue();
    next = rhs.getNext();
    return *this;
}

Koin::~Koin() = default;

double Koin::getValue() const
{
    return value;
}

Koin* Koin::getNext() const
{
    return next;
}

void Koin::setNext(Koin *next)
{
    Koin::next = next;
}

bool Koin::operator==(const Koin &rhs) const
{
    const Koin * temp = this;
    const Koin * temp_rhs = &(rhs);
    double sensitivity = Utilizer::doubleSensitivity();
    if(!temp_rhs && !temp)
        return true;
    else if(!temp_rhs || !temp)
        return false;
    else
    {
        while (temp && temp_rhs)
        {
            if((temp->getValue() - temp_rhs->getValue()) > sensitivity || (temp_rhs->getValue() - temp->getValue()) > sensitivity)
                return false;
            else
            {
                temp = temp->getNext();
                temp_rhs = temp_rhs->getNext();
            }
        }
        return !(temp || temp_rhs); // if there is any value left not compared
    }
}

bool Koin::operator!=(const Koin &rhs) const
{
    return !(*this == rhs);
}

Koin& Koin::operator*=(int multiplier)
{
    Koin::value = value * multiplier;
    return *this;
}

Koin& Koin::operator/=(int divisor)
{
    Koin::value = value / divisor;
    return *this;
}

std::ostream & operator<<(std::ostream& os,const Koin& koin)
{
    Koin * koin_next = koin.getNext();
    int flag = 1;
    int precision = Utilizer::koinPrintPrecision();
    os << std::fixed << std::setprecision(precision);
    while (flag || koin_next){
        if(flag)
        {
            os << koin.getValue() << "--";
            flag--;
        }
        else
        {
            os << koin_next->getValue() << "--";
            koin_next = koin_next->getNext();
        }
    }
    os << "|";
    return os;
}

void Koin::setValue(double value)
{
    Koin::value = value;
}