#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;

Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */

void Playlist::load(std::string fileName)
{
    ifstream file;
    string line;
    const char * array;
    int size;
    size = fileName.length();
    array = new char[size];
    array = fileName.c_str();
    file.open(array);
    while ( getline(file,line) )
    {
        string titlee,genree,yearr;
        size_t position = 0, i = 0;
        string token , delimeter = ";";
        while ((position = line.find(delimeter)) != string::npos || i == 2 ) {
            token = line.substr(0, position);
            switch (i)
            {
                case 0:
                    titlee = token;
                    break;
                case 1:
                    if(token != "")
                    {
                        genree = token;
                        break;
                    }
                    else
                    {
                        genree = "";
                        break;
                    }
                case 2:
                    if(token != "")
                    {
                        yearr = token;
                        break;
                    }
                    else
                    {
                        yearr = "";
                        break;
                    }
            }
            ++i;
            line.erase(0, position + delimeter.length());
        }
        Entry song(titlee,genree,yearr);
        entries.insertNode(entries.getTail(),song);
        HistoryRecord historyy(INSERT,song);
        history.push(historyy);
    }
}

void Playlist::insertEntry(const Entry &e)
{
    entries.insertNode(entries.getTail(),e);
    HistoryRecord historyy(INSERT,e);
    history.push(historyy);
}

void Playlist::deleteEntry(const std::string &_title)
{
    Node<Entry> * ptr = entries.getHead();
    if(ptr->getData().getTitle() == _title)
    {
        HistoryRecord historyy(DELETE,ptr->getData());
        entries.deleteNode(NULL);
        history.push(historyy);
        return;
    }
    while (ptr)
    {
        if(!ptr->getNext()->getNext())
            break;
        if(ptr->getNext()->getData().getTitle() == _title)
        {
            entries.deleteNode(ptr);
            HistoryRecord historyy(DELETE,ptr->getData());
            history.push(historyy);
            break;
        }
        ptr = ptr->getNext();
    }
}

void Playlist::moveLeft(const std::string &title)
{
    Node<Entry> * ptr = entries.getHead();
    if(ptr == NULL || ptr->getData().getTitle() == title || !(ptr->getNext()))//NULL VEYA TEK NODE
        return;
    else if(ptr->getNext()->getData().getTitle() == title)//2 NODE
    {
        Node<Entry> * target = ptr->getNext();
        ptr->setNext(target->getNext());
        target->setNext(ptr);
        entries.setHead(target);
        return;
    }
    while (ptr)// >2 NODE
    {
        if(ptr->getNext()->getNext())
        {
            if(ptr->getNext()->getNext()->getData().getTitle() == title)
            {
                Node<Entry> * target = ptr->getNext()->getNext();
                Node<Entry> * previous = ptr->getNext();
                ptr->setNext(target);
                previous->setNext(target->getNext());
                target->setNext(previous);
                if(previous->getNext() == NULL)
                    entries.setTail(previous);
                break;
            }
        }
        else
            break;
        ptr = ptr->getNext();
    }
}

void Playlist::moveRight(const std::string &title)
{
    Node<Entry> * ptr = entries.getHead();
    if(ptr == NULL || !(ptr->getNext())) //NULL VEYA TEK NODE
        return;
    else if(entries.getTail()->getData().getTitle() == title)// rightmost node
        return;
    else if(ptr->getData().getTitle() == title)//head moves right
    {
        Node<Entry> * after = ptr->getNext();
        ptr->setNext(after->getNext());
        after->setNext(ptr);
        entries.setHead(after);
        return;
    }
    while (ptr)
    {
        if(ptr->getNext()->getNext())
        {
            if(ptr->getNext()->getData().getTitle() == title)
            {
                Node<Entry> * target = ptr->getNext();
                Node<Entry> * after = target->getNext();
                ptr->setNext(after);
                target->setNext(after->getNext());
                after->setNext(target);
                if(target->getNext() == NULL)
                    entries.setTail(target);
                break;
            }
        }
        else
            break;
        ptr = ptr->getNext();
    }
}

void Playlist::reverse()
{
    HistoryRecord historyy(REVERSE);
    MyStack<Entry> stack;
    Node<Entry> * ptr = entries.getHead();
    history.push(historyy);
    while (ptr)
    {
        stack.push(ptr->getData());
        ptr = ptr->getNext();
    }
    entries.clear();
    Node<Entry> * top = stack.Top();
    entries.insertNode(NULL,top->getData());
    stack.pop();
    Node<Entry> * prev = entries.getHead();
    while (!stack.isEmpty())
    {
        top = stack.Top();
        entries.insertNode(prev,top->getData());
        stack.pop();
        prev = prev->getNext();
    }
}

void Playlist::sort()
{
    Node<Entry> * ptr = entries.getHead();
    for (; ptr ; ptr = ptr->getNext()) {   // For each pass
        Node<Entry> * minptr = ptr;
        if(!ptr->getNext())
            break;
        Node<Entry> * ptrr = ptr->getNext();
        for (; ptrr ; ptrr = ptrr->getNext()){// Find min of unsorted
            if (minptr->getData().getTitle() > ptrr->getData().getTitle())
                minptr = ptrr;
        }
        if(ptr == minptr)
            continue;
        swap(ptr, minptr);             // Swap it with the first
        Node<Entry> * temp = ptr;
        ptr = minptr;
        minptr = temp;
    }
}

void Playlist::swap(Node<Entry> * lhs, Node<Entry> * rhs)
{
    if(lhs == rhs)
        return;
    else if(entries.getHead() == lhs) //head swap
    {
        Node<Entry> * prev = entries.findPrev(rhs->getData());
        Node<Entry> * tmp = lhs;
        Node<Entry> * tmp2 = lhs->getNext();
        lhs->setNext(rhs->getNext());
        if(prev == lhs)
        {
            rhs->setNext(tmp);
            entries.setHead(rhs);
            if (lhs->getNext() == NULL)
                entries.setTail(lhs);
        }
        else {
            prev->setNext(lhs);
            rhs->setNext(tmp2);
            entries.setHead(rhs);
            if (lhs->getNext() == NULL)
                entries.setTail(lhs);
        }
    }
    else if(lhs->getNext() == rhs)
    {
        Node<Entry> * prev = entries.findPrev(lhs->getData());
        prev->setNext(rhs);
        lhs->setNext(rhs->getNext());
        rhs->setNext(lhs);
        if(lhs->getNext() == NULL)
            entries.setTail(lhs);
    }
    else
    {
        Node<Entry> * prev = entries.findPrev(rhs->getData());
        Node<Entry> * prev2 = entries.findPrev(lhs->getData());
        Node<Entry> * tmp = lhs->getNext();
        lhs->setNext(rhs->getNext());
        prev->setNext(lhs);
        rhs->setNext(tmp);
        prev2->setNext(rhs);
        if(lhs->getNext() == NULL)
            entries.setTail(lhs);
    }
}

void Playlist::merge(const Playlist &pl)
{
    Node<Entry> * ptr1 = entries.getHead();
    Node<Entry> * ptr2 = pl.entries.getHead();
    while(ptr2)
    {
        while(ptr1)
        {
            if(ptr2->getData().getTitle() < ptr1->getData().getTitle() )
            {
                if(ptr1 == entries.getHead())
                {
                    entries.insertNode(NULL, ptr2->getData());
                    break;
                }
                else
                {
                    Node<Entry> *prev = entries.findPrev(ptr1->getData());
                    entries.insertNode(prev, ptr2->getData());
                    break;
                }
            }
            else if(!ptr1->getNext())
            {
                entries.insertNode(ptr1, ptr2->getData());
                break;
            }
            ptr1 = ptr1 -> getNext();
        }
        ptr1 = entries.getHead();
        ptr2 = ptr2 -> getNext();
    }
}

void Playlist::shuffle()
{
    int temp;
    size_t n = entries.getSize();
    Node<Entry> * ptr = entries.getHead();
    Node<Entry> * ptr2 = entries.getHead();
    for (int i = 0; i < n-1; ++i) {
        int j = this->getRandomNumber(i,n);
        temp = i;
        while (temp>0)
        {
            ptr = ptr->getNext();
            --temp;
        }
        while (j>0)
        {
            ptr2 = ptr2->getNext();
            --j;
        }
        swap(ptr,ptr2);
        ptr = entries.getHead();
        ptr2 = entries.getHead();
    }
}

void Playlist::undo()
{
    Node<HistoryRecord> * topnode = history.Top();
    HistoryRecord lastaction = topnode->getData();
    if(lastaction.getOperation() == INSERT)
    {
        Entry lastinserted = lastaction.getEntry();
        Node<Entry> * prev = entries.findPrev(lastinserted);
        entries.deleteNode(prev);
        history.pop();
    }
    else if(lastaction.getOperation() == DELETE)
    {
        Entry lastdeleted = lastaction.getEntry();
        Node<Entry> * last = entries.getTail();
        entries.insertNode(last,lastdeleted);
        entries.setTail(last->getNext());
        history.pop();
    }
    else if(lastaction.getOperation() == REVERSE)
    {
        this->reverse();
        history.pop();
        history.pop();//in reverse function we save reverse again
    }
}
