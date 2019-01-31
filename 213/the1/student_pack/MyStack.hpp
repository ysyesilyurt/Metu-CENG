#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack{
    private:
    Node<T> *top;                
    public:
    /*Default constructor*/
    MyStack();                     					
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);  				
    /*destructor*/
    ~MyStack(); 
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);  	
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();
    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/* TO-DO: method implementations below */

template <class T>
MyStack<T>::MyStack(): top(NULL)
{

}

template <class T>
MyStack<T>::MyStack(const MyStack<T> &rhs)
{
    top = NULL;
    *this = rhs;
}

template <class T>
MyStack<T>::~MyStack()
{
    while (!isEmpty())
        pop();
}

template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T> &rhs)
{
    if (this != &rhs) {               // if not assigned to itself
        while (!isEmpty()) pop();   // delete former elements of lhs
        if (!rhs.top)                // if rhs is empty
            top = NULL;              // then just make lhs empty
        else {                          // else
            top = new Node<T>(rhs.top->getData()); // create a new node
            Node<T>* nextnode = rhs.top->getNext(); // nextnode shows second item of rhs
            Node<T>* topnode = top;           // topnode shows top item of lhs
            while (nextnode) {                     // while more item in rhs
                topnode->setNext(new Node<T>(nextnode->getData()));  // append a new node to lhs copy current item of rhs to this
                nextnode = nextnode->getNext();                  // move nextnode forward
                topnode = topnode->getNext();                  // move topnode forward
            }
            topnode->setNext(NULL);            // put NULL to end of lhs
        }
    }
    return *this;                      // return lhs for cascaded op.
}

template <class T>
bool MyStack<T>::isEmpty() const
{
    return top == NULL;
}

template <class T>
void MyStack<T>::push(const T &newItem) {
    Node<T> *newstacknode = new Node<T>(newItem);   // create a new node  insert the data
    newstacknode->setNext(top);             // link this node to the stack
    top = newstacknode;                     // update the stack top
}

template <class T>
void MyStack<T>::pop() {
    Node<T> *temp = top;
    top = top->getNext();           // update the stack top
    delete temp;
}

template <class T>
Node<T>* MyStack<T>::Top() const
{
    return top;
}

#endif /* MYSTACK_HPP */

