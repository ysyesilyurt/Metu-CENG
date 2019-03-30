cmake_minimum_required(VERSION 3.7)
project(hw2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp author_comparator.hpp book.cpp book.hpp bookstore.cpp bookstore.hpp bst.hpp title_comparator.hpp)
add_executable(hw2 ${SOURCE_FILES})