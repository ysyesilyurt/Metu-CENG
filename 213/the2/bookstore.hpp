#ifndef _bookstore_h__
#define _bookstore_h__

#include <string>
#include <iostream>

#include "bst.hpp"
#include "book.hpp"
#include "author_comparator.hpp"
#include "title_comparator.hpp"

class BookStore //do not change this file
{
  public:
    BookStore();
    void insert(const Book &);
    void remove(const std::string &);
    void remove(const std::string &, const std::string &);
    void removeAllBooksWithTitle(const std::string &);
    void makeAvailable(const std::string &);
    void makeUnavailable(const std::string &, const std::string &);
    void updatePublisher(const std::string &, const std::string &);

  public:
    void printPrimarySorted( ) const;
    void printSecondarySorted( ) const;
    void printTernarySorted( ) const;
    void printBooksWithISBN(const std::string &,
                            const std::string &,
                            unsigned short =0) const;
    void printBooksOfAuthor(const std::string &,
                            const std::string & ="a",
                            const std::string & ="{") const;

  private:
    typedef Book::SecondaryKey SKey;
    typedef BinarySearchTree<std::string, Book> BSTP;
    typedef BinarySearchTree<SKey, const Book *,
            AuthorComparator> BSTS;
    typedef BinarySearchTree<SKey, Book *,
            TitleComparator> BSTT;

  private:
    BSTP primaryIndex;
    BSTS secondaryIndex;
    BSTT ternaryIndex;
};

#endif
