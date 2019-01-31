#include "bookstore.hpp"

//Expected output is in "main_bookstore.out"

void printAllBooksSorted(const BookStore & store)
{
  std::cout << "All books (isbn sorted):" << std::endl;
  store.printPrimarySorted();
  std::cout << "---------------------------------" << std::endl;

  std::cout << "All books (author-title sorted):" << std::endl;
  store.printSecondarySorted();
  std::cout << "---------------------------------" << std::endl;

  std::cout << "All books (title-author sorted):" << std::endl;
  store.printTernarySorted();
  std::cout << "---------------------------------" << std::endl;
}

int main( )
{
  BookStore myStore;

  myStore.insert(Book("978-0143112228", "The Invention of Solitude", "Paul Auster",
                      "Penguin Books", 2007, 192));
  myStore.insert(Book("978-0312429003", "the brooklyn files: a novel", "paul AUSTER",
                      "Picador", 2009, 320));
  myStore.insert(Book("978-0140178135", "Leviathan", "Paul AUSTER",           
                      "Penguin Books", 1993, 274));
  myStore.insert(Book("978-0312428944", "Timbuktu: A Novel", "pAul AustEr",
                      "Picador", 2009, 192));
  myStore.insert(Book("978-0140431950", "Leviathan", "Thomas Hobbes",
                      "Penguin Classics", 1982, 736));
  myStore.insert(Book("0965913228", "Oracle", "Paul Auster",
                      "Penguin Books", 2003, 245));
  myStore.insert(Book("0321714113", "C++", "Barbara Moo",
                      "Addison-Wesley Professional", 2012, 976));
  myStore.insert(Book("1491903996", "C++", "Scott Meyer",
                      "O\'Reilly Media", 1995, 334));


  printAllBooksSorted(myStore);

  std::cout << "All books since 2003:" << std::endl;
  myStore.printBooksWithISBN("0", ":", 2003);
  std::cout << "---------------------------------" << std::endl;

  std::cout << "All books by PAUL AUSTER with titles in [\"c\", \"p\"]" << std::endl;
  myStore.printBooksOfAuthor("PAUL AUSTER", "c", "p");
  std::cout << "---------------------------------" << std::endl;

  std::cout << "All books by PAUL AUSTER" << std::endl;
  myStore.printBooksOfAuthor("PAUL AUSTER");
  std::cout << "---------------------------------" << std::endl;

  std::cout << "Books with title \"C++\" are now unavailable" << std::endl;
  myStore.makeUnavailable("C++", "Barbara Moo");
  myStore.makeUnavailable("C++", "Scott Meyer");
  printAllBooksSorted(myStore);

  std::cout << "Scott Meyer\'s book is now available" << std::endl;
  myStore.makeAvailable("1491903996");
  printAllBooksSorted(myStore);

  std::cout << "Paul Auster now works with \"Publisher X\"" << std::endl;
  myStore.updatePublisher("pAuL auSTeR", "Publisher X");
  printAllBooksSorted(myStore);

  std::cout << "Removing book with isbn 0965913228" << std::endl;
  myStore.remove("0965913228");
  printAllBooksSorted(myStore);

  std::cout << "Removing Paul Auster's book \"the brooklyn files: a novel\"" << std::endl;
  myStore.remove("THE brookLyn files: A noVel", "pAUL aUSTer");
  printAllBooksSorted(myStore);

  std::cout << "Removing all books with title \"C++\"" << std::endl;
  myStore.removeAllBooksWithTitle("c++");
  printAllBooksSorted(myStore);
  
  std::cout << "Removing all books with title \"Leviathan\"" << std::endl;
  myStore.removeAllBooksWithTitle("leviathan");
  printAllBooksSorted(myStore);

  return 0;
}
