#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {
  
  Node<int> left(0);
  Node<int> right(2);
  Node<int> root(1, &left, &right);

  BinaryTree<int> tree(&root);
  tree.travers();
  cout << tree.search(1);  
  return 0;
}
