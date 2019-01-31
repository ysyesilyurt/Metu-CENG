#ifndef _ARTICLE_H
#define _ARTICLE_H
#define EMPTY_INDEX -1
#define MARKED_INDEX -99
#define EMPTY_KEY ""
#define MAX_LOAD_FACTOR 0.65
#include <iostream>
#include <string>
#include <vector>
#include <utility> // for pair
#include <fstream> // for reading words from file

class Article
{
public: 
	// DONT CHANGE PUBLIC PART
	Article( int table_size,int h1_param, int h2_param );
	~Article();

	int get( std::string key, int nth, std::vector<int> &path ) const;
	int insert( std::string key, int original_index );
	int remove( std::string key, int nth );

	double getLoadFactor() const;
	void getAllWordsFromFile( std::string filepath );

	void printTable() const;
	// DONT CHANGE PUBLIC PART
private:
	// YOU CAN ADD PRIVATE MEMBERS AND VARIABLES TO THE PRIVATE PART
	std::pair<std::string, int>* table;

	int n; // Current number of the existing entries in hash table
	int table_size;
	int h1_param; 
	int h2_param;

	void expand_table();
	int hash_function( std::string& key, int i) const;
	int h1( int key ) const;
	int h2( int key ) const;
	
	int convertStrToInt( const std::string &key ) const;

	bool isPrime(int n) const;
	int nextPrimeAfter(int n) const;
	int firstPrimeBefore(int n) const;
	// YOU CAN ADD PRIVATE MEMBERS AND VARIABLES TO THE PRIVATE PART
};
#endif
