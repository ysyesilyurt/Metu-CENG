#include <iomanip>
#include "Blockchain.h"
#include "Utilizer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Blockchain::Blockchain(int idd) : id(idd), head(nullptr)
{

}

Blockchain::Blockchain(int idd, Koin *headd) : id(idd), head(headd)
{

}

Blockchain::Blockchain(const Blockchain &rhs) : id(rhs.getID())
{
    Koin * rhs_head = rhs.getHead();
    Koin * new_koinhead = new Koin(rhs_head->getValue());
    head = new_koinhead;
    rhs_head = rhs_head->getNext();
    while(rhs_head)
    {
        Koin * next_one = new Koin(rhs_head->getValue());
        head->setNext(next_one);
        rhs_head = rhs_head->getNext();
        head = head->getNext();
    }
}

Blockchain& Blockchain::operator=(Blockchain &&rhs) noexcept //assignment operator will only move the koins, wont copy!!
{
    if(this != &rhs)
    {
        Koin * temp;
        while (head)
        {
            temp = head;
            head = head->getNext();
            delete temp;
        }
        head = rhs.getHead();
        rhs.head = nullptr;
    }
    return *this;
}

Blockchain::~Blockchain()
{
    if(isSoft)
        return;
    else
    {
        Koin * temp;
        while(head)
        {
            temp = head;
            head = head->getNext();
            delete temp;
        }
    }
}

int Blockchain::getID() const
{
    return id;
}

Koin* Blockchain::getHead() const
{
    return head;
}

double Blockchain::getTotalValue() const
{
    Koin * temp = head;
    double result = .0;
    while (temp)
    {
        result += temp->getValue();
        temp = temp->getNext();
    }
    return result;
}

long Blockchain::getChainLength() const
{
    Koin * temp = head;
    long length = 0;
    while (temp)
    {
        length++;
        temp = temp->getNext();
    }
    return length;
}

void Blockchain::operator++()
{
    double newKoinValue = Utilizer::fetchRandomValue();
    Koin *newKoin = new Koin(newKoinValue); // Koin newKoin = Koin(newKoinValue); local variable would go away and no assignments would be possible!!
    Koin * temp = head;
    if(!head)
        head = newKoin;
    else
    {
        while (temp->getNext())
            temp = temp->getNext();
        temp->setNext(newKoin);
    }
}

void Blockchain::operator--()
{
    Koin * temp = head;
    if(!head) // head == nullptr
        return;
    else if(!head->getNext()) // has just head
    {
        delete head;
        head = nullptr;
    }
    else
    {
        while (temp->getNext()->getNext()) // reach to the node at the second from the last
            temp = temp->getNext();
        delete temp->getNext(); // delete last item
        temp->setNext(nullptr); // set last to null
    }
}

Blockchain& Blockchain::operator*=(int multiplier)
{
    if(!head)
        return *this;
    else
    {
        Koin * temp = head;
        while (temp)
        {
            temp->setValue(temp->getValue() * multiplier);
            temp = temp->getNext();
        }
    }
    return *this;
}

Blockchain& Blockchain::operator/=(int divisor)
{
    if(!head)
        return *this;
    else
    {
        Koin * temp = head;
        while (temp)
        {
            temp->setValue(temp->getValue() / divisor);
            temp = temp->getNext();
        }
    }
    return *this;
}

std::ostream & operator<<(std::ostream& os,const Blockchain& blockchain)
{
    Koin * chain_head = blockchain.getHead();
    int precision = Utilizer::koinPrintPrecision();
    os << std::fixed << std::setprecision(precision);
    os << "Block " << blockchain.getID() << ": ";
    if(!chain_head)
    {
        os << "Empty.";
        return os;
    }
    else
    {
        os << *(chain_head);
        os << "(" << blockchain.getTotalValue() << ")";
        return os;
    }
}
