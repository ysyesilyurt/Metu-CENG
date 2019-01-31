#include "book.hpp"
#include "title_comparator.hpp"
#include <iostream>

//Expected output is at "main_book.out" file

int main(void)
{
  Book b1("56465", "Name Of The Book", "Enver",
          "BIZ", 1999, 657);

  std::cout << b1 << std::endl;
  
  b1.setPublisher("Someone else");

  std::cout << b1 << std::endl;

  b1.setUnavailable();

  std::cout << b1 << std::endl;

  b1.setPages(5667);
  b1.setYear(232);

  std::cout << b1 << std::endl;

  Book b2("6546", "Here is a book", "Enver",
          "T", 3533, 565);

  std::cout << b2 << std::endl;

  TitleComparator isLessThan;

  std::cout << isLessThan(Book::SecondaryKey(b1), 
                          Book::SecondaryKey(b2)) << std::endl;
  std::cout << isLessThan(Book::SecondaryKey(b2), 
                          Book::SecondaryKey(b1)) << std::endl;

  Book b3("6546", "name of the book", "enVir",
          "Next", 5656, 233);

  std::cout << isLessThan(Book::SecondaryKey(b1), 
                          Book::SecondaryKey(b3)) << std::endl;
  std::cout << isLessThan(Book::SecondaryKey(b3), 
                          Book::SecondaryKey(b1)) << std::endl;

  return 0;
}
