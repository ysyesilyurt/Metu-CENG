#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
     
    cout<<"Testing load"<<endl;
    cout<<"-------------"<<endl;
    Playlist pl1 = Playlist(); 
    pl1.load("list.txt");
    pl1.print();
    pl1.printHistory();
    
    cout<<"Testing insert"<<endl;
    cout<<"-------------"<<endl;
    pl1.insertEntry(Entry("Rendez-Vous 2"));
    pl1.insertEntry(Entry("Equinoxe 4"));
    pl1.print();
    pl1.printHistory();
    
    cout<<"Testing delete"<<endl;
    cout<<"-------------"<<endl;
    pl1.deleteEntry("Billie Jean");
    pl1.print();
    pl1.printHistory();
    
    cout<<"Testing Move_left"<<endl;
    cout<<"-------------"<<endl;
    pl1.moveLeft("The Four Seasons");
    pl1.print();
    pl1.printHistory();  

    cout<<"Testing Reverse"<<endl;
    cout<<"-------------"<<endl;
    pl1.reverse();
    pl1.print();
    pl1.printHistory();  
    
    cout<<"Testing Sort"<<endl;
    cout<<"-------------"<<endl;
    pl1.sort();
    pl1.print();
    pl1.printHistory(); 
    
    cout<<"Testing Merge"<<endl;
    cout<<"-------------"<<endl;
    
    Playlist pl2 = Playlist(); 
    pl2.insertEntry(Entry("Sinnerman"));
    pl2.insertEntry(Entry("Oxygene 4"));
    pl1.sort();
    pl2.sort();
    pl1.merge(pl2);
    pl1.print();
    pl1.printHistory();
    
    cout<<"Testing Shuffle"<<endl;
    cout<<"-------------"<<endl;
    pl1.shuffle();
    pl1.print();
    pl1.printHistory();
    
    cout<<"Testing Undo1"<<endl;
    cout<<"-------------"<<endl;
    pl1.undo();
    pl1.print();
    pl1.printHistory();
            
    cout<<"Testing Undo2"<<endl;
    cout<<"-------------"<<endl;
    pl1.undo();
    pl1.print();
    pl1.printHistory();
    
	return 0;
}