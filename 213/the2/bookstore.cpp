#include "bookstore.hpp"

std::string convertlowercase(const std::string &);

BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)
{
    primaryIndex.insert(book.getISBN(),book);
    BSTP::Iterator item = primaryIndex.find(book.getISBN());
    SKey keyy((*item).getTitle(),(*item).getAuthor());
    secondaryIndex.insert(keyy,&(*item));
    ternaryIndex.insert(keyy,&(*item));
}

void
BookStore::remove(const std::string & isbn)
{
    BSTP::Iterator item = primaryIndex.find(isbn);
    if(item != primaryIndex.end())
    {
        SKey keyy((*item).getTitle(),(*item).getAuthor());
        primaryIndex.remove(isbn);
        secondaryIndex.remove(keyy);
        ternaryIndex.remove(keyy);
    }
}

void
BookStore::remove(const std::string & title,
                  const std::string & author)
{
    BSTP::Iterator item = primaryIndex.begin();
    if(item == primaryIndex.end())
        return;
    while (!((convertlowercase((*item).getTitle()) == convertlowercase(title)) && (convertlowercase((*item).getAuthor()) == convertlowercase(author))))
        ++item;
    SKey keyy((*item).getTitle(),(*item).getAuthor());
    primaryIndex.remove((*item).getISBN());
    secondaryIndex.remove(keyy);
    ternaryIndex.remove(keyy);
}

void
BookStore::removeAllBooksWithTitle(const std::string & title)
{
    SKey keyy1(title,"a");
    SKey keyy2(title,"{");
    std::list<BSTT::Iterator> itemrangelst = ternaryIndex.find(keyy1,keyy2);
    while (!itemrangelst.empty())
    {
        remove((*(itemrangelst.front()))->getISBN());
        itemrangelst.pop_front();
    }
}

void
BookStore::makeAvailable(const std::string & isbn)
{
    BSTP::Iterator item = primaryIndex.find(isbn);
    if(item != primaryIndex.end())
        (*item).setAvailable();
}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
    SKey keyy(title,author);
    BSTP::Iterator item = primaryIndex.begin();
    while (item != primaryIndex.end())
    {
        if((convertlowercase((*item).getTitle()) == convertlowercase(title)) && (convertlowercase((*item).getAuthor()) == convertlowercase(author)))
            (*item).setUnavailable();
        ++item;
    }
}

void
BookStore::updatePublisher(const std::string & author,
                           const std::string & publisher)
{
    BSTP::Iterator item = primaryIndex.begin();
    while (item != primaryIndex.end())
    {
        if(convertlowercase((*item).getAuthor()) == convertlowercase(author))
            (*item).setPublisher(publisher);
        ++item;
    }
}

void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
    std::list<BSTP::Iterator> itemrangelst = primaryIndex.find(isbn1,isbn2);
    std::list<BSTP::Iterator>::iterator it;
    for (it = itemrangelst.begin(); it != itemrangelst.end() ; ++it) {
        if((*(*it)).getYear() >= since)
            std::cout << *(*it) << std::endl;
    }
}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
    SKey keyy1(first,author);
    SKey keyy2(last,author);
    std::list<BSTS::Iterator> itemrangelst = secondaryIndex.find(keyy1,keyy2);
    for ( ; !itemrangelst.empty() ; itemrangelst.pop_front()) {
        std::cout <<  *(*(itemrangelst.front())) << std::endl;
    }
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

std::string convertlowercase(const std::string & word)
{
    std::string wordd = word;
    int i = 0;
    while (wordd[i])
    {
        wordd[i] = tolower(wordd[i]);
        i++;
    }
    return wordd;
}
