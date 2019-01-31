#include "book.hpp"

//do not change this file

Book::Book(const std::string & _isbn, const std::string & _title,
           const std::string & _author, const std::string & _publisher,
           unsigned short _year, unsigned short _pages, bool _status)
  : isbn(_isbn), title(_title), author(_author)
{
  publisher = _publisher;
  year = _year;
  pages = _pages;
  status = _status;
}

const Book &
Book::operator=(const Book & rhs)
{
  publisher = rhs.publisher;
  year = rhs.year;
  pages = rhs.pages;
  status = rhs.status;

  return *this;
}

const std::string & 
Book::getISBN( ) const
{
  return isbn;
}

const std::string & 
Book::getTitle( ) const
{
  return title;
}

const std::string & 
Book::getAuthor( ) const
{
  return author;
}
     
unsigned short
Book::getYear( ) const
{
  return year;
}

void 
Book::setPublisher(const std::string & _publisher)
{
  publisher = _publisher;
}

void 
Book::setYear(unsigned short _year)
{
  year = _year;
}

void 
Book::setPages(unsigned short _pages)
{
  pages = _pages;
}

void 
Book::setAvailable( )
{
  status = true;
}

void
Book::setUnavailable( )
{
  status = false;
}

std::ostream &
operator<<(std::ostream & out, const Book & book)
{
  std::string sep(" | ");

  out << book.isbn << sep << book.title << sep
      << book.author << sep << book.publisher << sep
      << book.year << sep << book.pages << sep
      << (book.status ? 'T' : 'F');

  return out;
}

Book::SecondaryKey::SecondaryKey(const Book & book)
  : title(book.title), author(book.author)
{
}

Book::SecondaryKey::SecondaryKey(const std::string & _title,
                                 const std::string & _author)
  : title(_title), author(_author)
{
}

const std::string &
Book::SecondaryKey::getTitle( ) const
{
  return title;
}

const std::string &
Book::SecondaryKey::getAuthor( ) const
{
  return author;
}
