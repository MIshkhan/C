#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {
  
  int size;
  int root;
  double data;
  
  cout << "Enter number of nodes: ";
  cin >> size;
  cout << "Enter root value: " ;
  cin >> root;  
  
  BinaryTree<double> tree( new Node<double>(root) );
  for(int i = 1; i < size; ++i) {
    cout << "Input node value: ";
    cin >> data;
    tree.insert(data);
  }
/*
  stree.drop(1);
  tree.travers();  
  cout << endl;
  cout << "Number of leaves: " << tree.countLeaves() << endl; 
  cout << "Width in 1 level: " << tree.getWidth(1) << endl;   
  cout << "Width in 2 level: " << tree.getWidth(2) << endl; 
  cout << "Maximum width: " << tree.getMaxWidth() << endl; 
  cout << "Height: " << tree.height() << endl; 
  cout << "Level order: "; tree.printLevelOrder(); cout << endl; 
*/
  cout << "Interactive inorder: "; tree.iterativeInorder(); cout << endl; 
  cout << "Interactive preorder: "; tree.iterativePreorder(); cout << endl; 
  cout << "Sum of nodes: " << tree.sum() << endl;
  cout << "Is tree full: " << tree.full() << endl;
  return 0;
}
