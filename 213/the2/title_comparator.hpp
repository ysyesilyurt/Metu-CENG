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
        std::string title1 = key1.getTitle();
        std::string author1 = key1.getAuthor();
        std::string title2 = key2.getTitle();
        std::string author2 = key2.getAuthor();
        int i = 0;
        while (title1[i])
        {
            title1[i] = tolower(title1[i]);
            i++;
        }
        i = 0;
        while (title2[i])
        {
            title2[i] = tolower(title2[i]);
            i++;
        }
        i = 0;

        if (title1 < title2)
            return true;

        else if (title1 == title2)
        {
            while (author1[i])
            {
                author1[i] = tolower(author1[i]);
                i++;
            }
            i = 0;
            while (author2[i])
            {
                author2[i] = tolower(author2[i]);
                i++;
            }
            if(author1 < author2)
                return true;
            else
                return false;
        }
        else
            return false;
    }

};

#endif
