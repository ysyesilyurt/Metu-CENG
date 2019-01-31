#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.hpp"
#include <sstream>
#include <string>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
		

class tmpClass{
    public:
        tmpClass(string val1 = "", int val2 = 0): s_val(val1), i_val(val2) {};
        friend ostream &operator<<(ostream &out, const tmpClass& r){
            out << r.s_val << "-" << r.i_val<<";";
            return out;
        };
    private:
        string s_val;
        int i_val;
};


void testPrint(){
    srand (15);
    LinkedList<tmpClass> list = LinkedList<tmpClass>();
    list.print();
    for (int i = 0; i < 20; ++i){
        list.insertNode(list.getHead(),tmpClass(SSTR(rand()%10), rand()%10));
    }
    list.print();
}

void testCopy(){
    srand (17);
    LinkedList<tmpClass> list = LinkedList<tmpClass>();
    for (int i = 0; i < 5; ++i){
        list.insertNode(list.getHead(),tmpClass(SSTR(rand()%10), rand()%10));
    }
    list.print();
    LinkedList<tmpClass> list2 = list;
    list2.print();
    LinkedList<tmpClass> list3;
    list3 = list2;
    list3.print();
}


int main(int argc, char* argv[]){

    cout << endl << "TEST 1" << endl;
    testPrint();

    cout << endl << "TEST 2" << endl;
    testCopy();

    return 0;
}		