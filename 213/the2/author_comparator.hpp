#ifndef _author_h__
#define _author_h__

#include "book.hpp"
#include <cstring>

class AuthorComparator
{
  public:
    bool operator( ) (const Book::SecondaryKey & key1, 
                      const Book::SecondaryKey & key2) const
    {
      //if key1 is less than key2 wrt specifications
      //return true
      //otherwise
      //return false
    }

};

#endif
