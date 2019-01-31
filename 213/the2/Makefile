CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: bookstore

bookstore: main.o book.o bookstore.o
	$(CC) main.o book.o bookstore.o -o bookstore

main.o: main_bookstore.cpp
	$(CC) $(CFLAGS) main_bookstore.cpp -o main.o

book.o: book.cpp book.hpp
	$(CC) $(CFLAGS) book.cpp

bookstore.o: bookstore.cpp bookstore.hpp bst.hpp book.hpp author_comparator.hpp title_comparator.hpp
	$(CC) $(CFLAGS) bookstore.cpp

clean:
	rm *o
