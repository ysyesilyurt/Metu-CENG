#include <iostream>
#include <cmath>

#include "bst.hpp"

//Expected output is at "test_tree.out" file

template <typename K, typename O, typename C>
void
printTreeInfo(const BinarySearchTree<K,O,C> & tree)
{
  if (tree.empty())
  {
    std::cout << "Tree is empty." << std::endl;
  }
  else
  {
    std::cout << "Tree includes " << tree.size() << " node(s)"
              << " and has height " << tree.height()
              << ", and an ideally balanced tree of this size"
              << " has height " << floor(log2(tree.size()))
              << "." << std::endl;
  }
}

template <typename K, typename O, typename C>
void
print(const BinarySearchTree<K,O,C> & tree)
{
  tree.print(std::cout); //to console
  printTreeInfo(tree);
}

template <typename K, typename O, typename C>
void
traverseDataItems(const BinarySearchTree<K,O,C> & tree)
{
  typename BinarySearchTree<K,O,C>::Iterator it;

  for (it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename K, typename O, typename C>
void
insertAndPrint(BinarySearchTree<K,O,C> & tree, const K & key, const O & data)
{
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Inserting key, value pair (" 
            << key << ", " << data << ") :" << std::endl;
  
  tree.insert(key, data);
  print(tree);
}

template <typename K, typename O, typename C>
void //operator+ is assumed to be defined for type O
incrementDataAndTraverseValues(BinarySearchTree<K,O,C> & tree, 
                               const K & key, const O & amount)
{
  typename BinarySearchTree<K,O,C>::Iterator it = tree.find(key);

  if (it == tree.end())
  {
    ;
  }
  else
  {
    *it = *it + amount;
  }

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Traversing data values in the tree after incrementing" 
            << " value at key " << key << " by " 
            << static_cast<int>(amount) 
            << "\nIn other words capitalizing \'"
            << static_cast<unsigned char>(key) << '\'' << std::endl;
  
  traverseDataItems(tree);
}

template<typename K, typename O, typename C>
void
printValuesWhoseKeysAreWithinRange(const BinarySearchTree<K,O,C> & tree,
                                   const K & lower, const K & upper)
{
  C isLessThan;

  K low = isLessThan(lower, upper) ? lower : upper;
  K upp = isLessThan(upper, lower) ? lower : upper;

  std::list<typename BinarySearchTree<K,O,C>::Iterator> 
    lst = tree.find(low, upp);

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "There are " << lst.size() << " data values whose keys "
            << "fall within range (" << low << ", " << upp << ") a.k.a. "
            << '(' << static_cast<unsigned char>(low) << ", "
            << static_cast<unsigned char>(upp) << ") :" << std::endl;

  typename // :( use typedefs
  std::list<typename BinarySearchTree<K,O,C>::Iterator>::const_iterator it;

  for (it = lst.begin(); it != lst.end(); ++it)
  {
    std::cout << *(*it) << " ";
  }
  std::cout << std::endl;
}
                                  
template <typename K, typename O, typename C>
void
removeAndPrint(BinarySearchTree<K,O,C> & tree, const K & key)
{
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Removing key " << key << " :" << std::endl;
  
  tree.remove(key);
  print(tree);
}

template <typename K, typename O, typename C>
void
printIfEmpty(const BinarySearchTree<K,O,C> & tree)
{
  if (tree.empty())
  {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Initially we have the empty tree :" << std::endl;
    
    print(tree);
  }
}

int main(void)
{
  BinarySearchTree<int, char> bst; //operator< is used to compare int's
  
  printIfEmpty(bst);
  
  int  toInsertKeys   [] = {97, 104, 102, 115, 100, 110, 122, 107};
  char toInsertValues [] = {'a', 'h', 'f', 's', 'd', 'n', 'z', 'k'};
  size_t items = 8;

  for (size_t i = 0; i < items; ++i)
  {
    insertAndPrint(bst, toInsertKeys[i], toInsertValues[i]);
  }

  printValuesWhoseKeysAreWithinRange(bst, 55, 111);
  printValuesWhoseKeysAreWithinRange(bst, 110, 102);

  int toUpdate  [] = {91, 97, 102, 104, 115, 122, 55};
  size_t to_upd = 7;

  for (size_t i = 0; i < to_upd; ++i)
  {
    incrementDataAndTraverseValues(bst, toUpdate[i], 
                                   static_cast<char>('A'-'a'));
  }

  printValuesWhoseKeysAreWithinRange(bst, 122, 102);
  printValuesWhoseKeysAreWithinRange(bst, 100, 110);
  
  int toRemove [] = {110, 102, 115, 104, 122, 110, 100, 107, 32, 97, 102};
  size_t keys = 11;

  for (size_t i = 0; i < keys; ++i)
  {
    removeAndPrint(bst, toRemove[i]);
  }

  return 0;
}
