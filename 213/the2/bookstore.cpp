#include "bookstore.hpp"

BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)
{
}

void
BookStore::remove(const std::string & isbn)
{
}

void
BookStore::remove(const std::string & title,
                  const std::string & author)
{
}

void
BookStore::removeAllBooksWithTitle(const std::string & title)
{
}

void
BookStore::makeAvailable(const std::string & isbn)
{
}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
}

void
BookStore::updatePublisher(const std::string & author, 
                           const std::string & publisher)
{
}

void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
}

void //implemented, do not change
BookStore::printPrimarySorted( ) const
{
  BSTP::Iterator it;

  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void //implemented, do not change
BookStore::printSecondarySorted( ) const
{
  BSTS::Iterator it;

  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

void //implemented, do not change
BookStore::printTernarySorted( ) const
{
  BSTT::Iterator it;

  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

