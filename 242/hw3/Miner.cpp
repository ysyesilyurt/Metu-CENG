#include <iomanip>
#include "Miner.h"
#include "Utilizer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

int Miner::getNextAvailableBlockchainID() const
{
    return last_blockchainID + 1;
}

Miner::Miner(std::string name)
{
    minerChain.emplace_back(std::pair <Blockchain *,bool> (nullptr, false));
    last_blockchainID = -1;
    Miner::name = std::move(name); // moves the string, to get rid of reduntant copies
}

Miner::~Miner()
{
    unsigned long size = minerChain.size(), index = 0;
    while(index < size)
    {
        delete minerChain[index].first;
        index++;
    }
}

void Miner::createNewBlockchain()
{
    if(!minerChain[0].first) // no head
    {
        minerChain[0].first = new Blockchain(getNextAvailableBlockchainID());
        last_blockchainID += 1;
    }
    else
    {
        minerChain.emplace_back(std::pair <Blockchain *,bool> (new Blockchain(getNextAvailableBlockchainID()), false));
        last_blockchainID += 1;
    }
}

void Miner::mineUntil(int cycleCount)
{
    unsigned long size = minerChain.size(), index;
    for (int i = 0; i < cycleCount; ++i) {
        index = 0;
        while(index < size)
        {
            ++(*minerChain[index].first);
            index++;
        }
    }
}

void Miner::demineUntil(int cycleCount)
{
    unsigned long size = minerChain.size(), index;
    int flag;
    for (int i = 0; i < cycleCount; ++i) {
        index = 0;
        while(index < size)
        {
            if(!minerChain[index].first->getHead()) // blockchain has no value left
                return;
            flag = 0;
            if(minerChain[index].second) // softforked blockchain
            {
                if(!minerChain[index].first->getHead()->getNext()) // if just head remains in the softforked blockchain
                    index++;
                else
                {
                    --(*minerChain[index].first);
                    index++;
                }
            }
            else
            {
                Koin * tempKoin = minerChain[index].first->getHead(); // last Koin to be demined
                while(tempKoin->getNext())
                    tempKoin = tempKoin->getNext();
                for (int j = 0; j < softforkedChains.size(); ++j)
                {
                    if(tempKoin->getValue() == softforkedChains[j].second) // if the value to be demined is the head of any softforked
                    {
                        flag++;
                        break;
                    }
                }
                if(!flag)
                {
                    --(*minerChain[index].first);
                    index++;
                }
                else
                    index++;
            }
        }
    }
}

double Miner::getTotalValue() const // Soft-forks DO NOT constitute for the total value of the miner.
{
    unsigned long size = minerChain.size(), index = 0;
    double  result = .0;
    while(index < size)
    {
        if(minerChain[index].second) // softforked
            index++;
        else
        {
            result += minerChain[index].first->getTotalValue();
            index++;
        }
    }
    return result;
}

long Miner::getBlockchainCount() const
{
    return last_blockchainID + 1;
}

Blockchain* Miner::operator[](int id) const
{
    unsigned long size = minerChain.size(), index = 0;
    while(index < size)
    {
        if(id == minerChain[index].first->getID())
            return minerChain[index].first;
        else
            index++;
    }
    return nullptr;
}

bool Miner::softFork(int blockchainID)
{
    Blockchain * blkchn_toCopy = (*this)[blockchainID];
    if(!blkchn_toCopy) // fork blockchain dne
        return false;
    else
    {
        Koin * lastKoin = blkchn_toCopy->getHead();
        if(lastKoin)
        {
            while (lastKoin->getNext())
                lastKoin = lastKoin->getNext();
            int nextID = getNextAvailableBlockchainID();
            last_blockchainID += 1;
            Blockchain * newBlockchain= new Blockchain(nextID,lastKoin);
            newBlockchain->isSoft = true;
            minerChain.emplace_back(std::pair <Blockchain *,bool> (newBlockchain, true));
            softforkedChains.emplace_back(std::pair <int,double> (newBlockchain->getID(),newBlockchain->getHead()->getValue()));
        }
        else
            this->createNewBlockchain();
    }
    return true;
}

bool Miner::hardFork(int blockchainID)
{
    Blockchain * blkchn_toCopy = (*this)[blockchainID];
    if(!blkchn_toCopy) // fork blockchain dne
        return false;
    else
    {
        Koin * lastKoin = blkchn_toCopy->getHead();
        if(lastKoin)
        {
            while (lastKoin->getNext())
                lastKoin = lastKoin->getNext();
            int nextID = getNextAvailableBlockchainID();
            last_blockchainID += 1;
            Koin * newLastKoin = new Koin(lastKoin->getValue());
            Blockchain * newBlockchain = new Blockchain(nextID,newLastKoin);
            minerChain.emplace_back(std::pair <Blockchain *,bool> (newBlockchain, false));
        }
        else
            this->createNewBlockchain();
    }
    return true;
}

std::ostream & operator<<(std::ostream& os,const Miner& miner)
{
    int precision = Utilizer::koinPrintPrecision();
    unsigned long size = miner.getChain().size(), index = 0;
    os << std::fixed << std::setprecision(precision);
    os << "-- BEGIN MINER --\n" << "Miner name: " << miner.name << "\nBlockchain count: ";
    os << miner.getBlockchainCount() << "\n";
    os << "Total value: " << miner.getTotalValue() << "\n\n";
    while (index < size)
    {
        os << *miner.getChain()[index].first;
        os << '\n';
        index++;
    }
    os << "\n-- END MINER --\n";
    return  os;
}


std::vector< std::pair<Blockchain *,bool> > Miner::getChain() const
{
    return minerChain;
}
