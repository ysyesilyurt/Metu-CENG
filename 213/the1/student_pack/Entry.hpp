#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <cstdlib>
#include <iostream>
#include <string>

class Entry {
private:
	std::string title;
	std::string genre;
	std::string year;
public:
	Entry();  
        /* This constructor is the only way to set private members of the class*/
	Entry(std::string _title, std::string _genre="", std::string _year="");
        /*return Title of the entry*/
	std::string getTitle() const;
        /*return Genre of the entry*/
	std::string getGenre() const;
        /*return year of the entry*/
	std::string getYear() const;
        /* You are expected to overload the “==” operator. 
         * If the “title”s of two entries are same, this method returns true*/
	bool operator==(const Entry & rhs) const; 
        /*This method will be used to print an entry
         It was already implemented and you should not edit this method*/
	friend std::ostream &operator<<(std::ostream &out, const Entry& t);
};


#endif
