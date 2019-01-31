#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T> 
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
	size_t  size; 
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* Return head of the linked-list*/
        Node<T>* getHead() const;
        /* Set head of the linked-list*/
        void setHead(Node<T>* n);
        /* Return tail of the linked-list*/
        Node<T>* getTail() const;
        /* Set tail of the linked-list*/
        void setTail(Node<T>* n);
        /* Get the previous node of the node that contains the data item. 
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* Get the node that stores the data item. 
         * If data is not found in the list, this function returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* Insert a new node to store the data item. 
         * The new node should be placed after the “prev” node. 
         * If prev is NULL then insert new node to the head.*/
        void insertNode(Node<T>* prev, const T& data); 
        /* This method is used to delete the node that is next to “prevNode”. 
         * PS:prevNode is not the node to be deleted. */
        void deleteNode(Node<T>* prevNode);  
        /* This method is used to clear the contents of the list.*/
        void clear();
        /* This method returns true if the list empty, otherwise returns false.*/
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /*Prints the list. This method was already implemented. Do not modify.*/
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */
template <class T>
LinkedList<T>::LinkedList(): head(NULL), tail(NULL) , size(0)
{

}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll)
{
    head = tail = NULL;
    size = 0;
    *this=ll;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
{
    if (this != &ll) {
        clear();              // clear the former content
        const Node<T>* r = ll.getHead(); // r = the zeroth of ll
        Node<T>* nodee = new Node<T>(r->getData());    // nodee is the new scratch
        head = nodee;
        r = r->getNext();
        while (r) {         // while more element in ll
                            // insert a new node to the end of ll with the value of ll pointed by r
            insertNode(nodee , r->getData());
            r = r -> getNext();              // move r forward
            nodee = nodee->getNext();              // move nodee forward
        }
        tail = nodee;
    }
    return *this;     // return ll for cascading assignment
}

template <class T>
LinkedList<T>::~LinkedList()
{
    clear();       // delete all the elements, except head
    delete head;  // delete head
}

template <class T>
Node<T>* LinkedList<T>::getHead() const
{
    return head;
}

template <class T>
void LinkedList<T>::setHead(Node<T>* n)
{
    head=n;
}

template <class T>
Node<T>* LinkedList<T>::getTail() const
{
    return tail;
}

template <class T>
void LinkedList<T>::setTail(Node<T>* n)
{
    tail=n;
}

template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const
{
    Node<T>* nodee = getHead();
    if(nodee->getData() == data)
        return NULL;
    while (nodee->getNext())
    {
        if(nodee->getNext()->getData() == data)
            return nodee;
        nodee = nodee->getNext();
    }
    return NULL;
}

template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const
{
    Node<T>* nodee = getHead();
    while (nodee) {   // while p shows some node
        // if data in the node pointed by p is what we search for,
        // then return its address
        if (nodee->getData() == data)
            return nodee;
        nodee = nodee->getNext();
    }
    return NULL;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data)
{
    size++;
    if (prev != NULL) {    // non-empty list
        if(prev->getNext() == NULL) //insertion to end
        {
            Node<T>* newNode = new Node<T>(data);
            newNode->setNext(prev->getNext());
            prev->setNext(newNode);
            tail=newNode;
        }
        else {      //insertion to middle
            // create a new node whose next will point to prev’s next
            Node<T> *newNode = new Node<T>(data);
            newNode->setNext(prev->getNext());
            // now prev’s next will be this new node
            prev->setNext(newNode);
        }
    }
    else {   // Insertion before the head (or to an empty list)
        if(isEmpty()) // empty list
        {
            Node<T>* newNode = new Node<T>(data);
            newNode->setNext(head);
            tail = head = newNode;
        }
        else { //insertion to before the head
            // create a new node whose next will point to the first node
            Node<T> *newNode = new Node<T>(data);
            newNode->setNext(head);
            // now this new node will be the first of the list
            head = newNode;
        }
    }
}

template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode)
{
    size--;
    if(prevNode!=NULL)
    {
        if(prevNode->getNext() == tail)
        {
            Node<T>* target = prevNode->getNext();
            prevNode->setNext(target->getNext());
            delete target;
            tail = prevNode;
        }
        else {
            Node<T> *target = prevNode->getNext();
            prevNode->setNext(target->getNext());
            delete target;
        }
    }
    else
    {
       if(isEmpty())
           delete head;
       else//head delete
       {
           Node<T> *target = head;
           head = head->getNext();
           delete target;
       }
    }
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return head == NULL;   // if NULL, then it is empty
}

template <class T>
void LinkedList<T>::clear() //NULL KALIYOR ICERDE!!!
{
    Node<T>* temp;
    while(!isEmpty())
    {
        temp = head;
        head = head->getNext();
        delete temp;
    }
    size = 0;
}

template <class T>
size_t LinkedList<T>::getSize() const
{
    return size;
}

/* end of your implementations*/

#endif
