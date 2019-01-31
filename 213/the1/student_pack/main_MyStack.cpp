#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MyStack.hpp"
#include <sstream>
#include <string>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

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
    MyStack<tmpClass> s = MyStack<tmpClass>();
    s.print();
    for (int i = 0; i < 20; ++i){
        s.push(tmpClass(SSTR(rand()%10), rand()%10));
    }
    s.print();
}

void testCopy(){
    srand (17);
    MyStack<tmpClass> s = MyStack<tmpClass>();
    for (int i = 0; i < 5; ++i){
        s.push(tmpClass(SSTR(rand()%10), rand()%10));
    }
    s.print();
    MyStack<tmpClass> s2 = s;
    s2.print();
    MyStack<tmpClass> s3;
    s3 = s2;
    s3.print();
}

int main(int argc, char* argv[]){

    cout << endl << "TEST 1" << endl;
    testPrint();

    cout << endl << "TEST 2" << endl;
    testCopy();

    return 0;
}