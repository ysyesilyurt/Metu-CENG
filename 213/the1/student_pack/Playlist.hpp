#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <string>
#include "LinkedList.hpp"
#include "Entry.hpp"
#include "HistoryRecord.hpp"
#include "MyStack.hpp"


class Playlist {
private:
	LinkedList<Entry> entries;	
	MyStack< HistoryRecord > history; 
	/* Generate a random integer such that i ≤ j < n */
	int getRandomNumber(int i, int n) const;
    /*swap helper function*/
    void swap(Node<Entry> * lhs, Node<Entry> * rhs);
public:	
	Playlist();
	/*load the list of playlist entries from the given file.*/
	void load(std::string fileName);
	/*Inserts a new entry to the end of playlist entries. 
	 *For UNDO operation, you should save the insert operation.*/
	void insertEntry(const Entry &e); 
	/*Deletes the entry with given title from the list. 
	 *If the delete operation is successful (i.e. the entry with given title is in the playlist and deleted successfully)..
	 *you should save the this  operation for UNDO operation.*/
	void deleteEntry(const std::string &_title);
	/*Moves the entry with given title to the left.*/
	void moveLeft(const std::string &title); 
	/*Moves the entry with given title to the right.*/
	void moveRight(const std::string &title);
	/*Reverse the playlist entries.*/
	void reverse();
	/*Sort the entries of the playlist from lowest to highest according to their “title”s.*/
	void sort(); 
	/*Merge the sorted lists while keeping the sort order*/
	void merge(const Playlist & pl); 
	/*Shuffle the playlist entries. Use getRandomNumber function to generate a random number. */
	void shuffle(); 
	/*UNDO the the operations*/
	void undo(); 
	/*print the list entries. It is already implemented. DO NOT MODIFY*/
	void print();
	/*Prints the contents of the history stack from top to bottom.*/
	void printHistory();
};



#endif

