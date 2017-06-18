#include <iostream>
#include <fstream>
#include <set>

using namespace std;

struct node {
  std::string key;
  unsigned char height;
  node* left;
  node* right;
  node(std::string k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p) {
  return p ? p->height : 0;
}

int bfactor(node* p) {
  return height( p->right ) - height( p->left );
}

void fixHeight(node* p) {
  unsigned char hl = height(p->left);
  unsigned char hr = height(p->right);
  p->height = ( hl > hr ? hl : hr ) + 1;
}

node* rotateRight(node* p) {
  node* q = p->left;
  p->left = q->right;
  q->right = p;
  fixHeight(p);
  fixHeight(q);
  return q;
}

node* rotateLeft(node* q) {
  node* p = q->right;
  q->right = p->left;
  p->left = q;
  fixHeight(q);
  fixHeight(p);
  return p;
}

node* balance(node* p) {
  fixHeight(p);
  if( bfactor(p)==2 ) {
    if( bfactor(p->right) < 0 )
      p->right = rotateRight(p->right);
    return rotateLeft(p);
  }
  if( bfactor(p)==-2 ) {
    if( bfactor(p->left) > 0  )
      p->left = rotateLeft(p->left);
    return rotateRight(p);
  }
  return p; 
}

node* insert(node* p, std::string k) {
  if( !p ) return new node(k);
  if( k < p->key )
    p->left = insert( p->left, k );
  else
    p->right = insert( p->right, k );
  return balance(p);
}

node* findMin(node* p) {
  return p->left ? findMin( p->left ) : p;
}

node* removeMin(node* p) {
  if( p->left==0 )
    return p->right;
  p->left = removeMin( p->left );
  return balance(p);
}

node* remove(node* p, std::string k) {
  if( !p ) return 0;
  if( k < p->key )
    p->left = remove( p->left, k );
  else if( k > p->key )
    p->right = remove( p->right, k );
  else {
    node* q = p->left;
    node* r = p->right;
    delete p;
    if( !r ) return q;
    node* min = findMin(r);
    min->right = removeMin(r);
    min->left = q;
    return balance(min);
  }
  return balance(p);
}

void printTree(node* p) {
  if(!p) {
    cout << "Empty tree";
    return;
  }
  cout << p->key;
  if(p->left) {
    cout << " { ";
    printTree(p->left);
    cout << " } ";
  }
  if(p->right) {
    cout << " { ";
    printTree(p->right);
    cout << " } ";
  }
}

int main(int argc, char* argv[]){
  node* root = 0;

  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    fstream f;
    string value;
    int size;
    set<string> extractableWords;
      
    cout << "How many words do you want to remove ? ";
    cin >> size;
    
    for(int i = 0; i < size; ++i) {
      cin >> value;
      extractableWords.insert(value);
    }
    
    f.open(argv[1], ios::in);
    if(f >> value) {
      root = new node(value);
      while(f >> value) {
	root = insert(root, value);
      }
    }
  }
  
  printTree(root);
  cout << endl;
  
  return 0;
}

// ------AVL TREE------
// INPUT: A C B F G E D
//
//         C
//        /  \
//       B    F
//      /    / \
//     A    E   G
//         /
//        D
//
// OUTPUT: C { B { A }  }  { F { E { D }  }  { G }  } 

 
