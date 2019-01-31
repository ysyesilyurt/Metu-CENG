#ifndef _book_h__
#define _book_h__

#include <string>
#include <ostream>

class Book //do not change this file
{
  public:
    Book(const std::string &, const std::string &,
         const std::string &, const std::string &,
         unsigned short, unsigned short =0, bool =true);

    const Book & operator=(const Book &);

    const std::string & getISBN( ) const; //main index
    const std::string & getTitle( ) const; //part of second index
    const std::string & getAuthor( ) const; //part of second index
    
    unsigned short getYear( ) const;

    void setPublisher(const std::string &);
    void setYear(unsigned short);
    void setPages(unsigned short);

    void setAvailable( );
    void setUnavailable( );

    class SecondaryKey;

    friend std::ostream & operator<<(std::ostream &, const Book &);

  private:
    const std::string isbn;
    const std::string title;
    const std::string author;
    std::string publisher;
    unsigned short year;
    unsigned short pages;
    bool status;
};


class Book::SecondaryKey
{
  public:
    SecondaryKey(const Book &);
    SecondaryKey(const std::string &, const std::string &);

    const std::string & getTitle( ) const;
    const std::string & getAuthor( ) const;

  private:
    const std::string title;
    const std::string author;

  private: //cannot be reassigned, no implementation provided
    const SecondaryKey & operator=(const SecondaryKey &);
};

#endif
