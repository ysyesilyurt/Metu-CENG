#ifndef _title_h__
#define _title_h__

#include "book.hpp"
#include <cstring>

class TitleComparator
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
