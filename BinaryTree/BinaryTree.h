#ifndef binaryTree_h
#define binaryTree_h

using namespace std;

template<typename T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;
	Node() : data(0), left(NULL), right(NULL) {}
	Node(T d, Node* l = NULL, Node* r = NULL) : data(d), left(l), right(r) {}
};

template<typename T>
class BinaryTree {
private:
	Node<T>* root;
  
public:
  /* BinaryTree(Element<T>* arr int size) { */
  /*   Node<T>** matrix = new Node<T>*[size]; */
  /*   for(int i(0); i < size; ++i) */
  /*     matrix[i] = new Node<T>(arr[i].data); */
  /*   root = matrix[0]; */
  /*   for(int i(0); i < size; ++i) { */
  /*     if( arr[i].right != -1 ) */
  /*       matrix[i]->right = matrix[arr[i].right]; */
  /*     if( arr[i].left != -1 ) */
  /*       matrix[i]->left = matrix[arr[i].left];       */
  /*   } */
  /* } */
  
	BinaryTree(Node<T>* r = 0) : root(r) {};

	void travers() {
		inorder(root);
		cout << endl;
		preorder(root);
	}

	void inorder(Node<T>* root) {
		if (root == NULL) return;
		inorder(root->right);
		cout << root->data << " ";
		inorder(root->left);
	}

	void preorder(Node<T>* root) {
		if (root == NULL) return;
		cout << root->data << " ";
		preorder(root->right);
		preorder(root->left);
	}
	
	bool isEmpty() { return root == NULL; }

  bool search(T element) {
    Node<T>* current = root; // Start from the root
    while (current != NULL)
      if (element < current->data) {
        current = current->left; // Go left
      }
      else if (element > current->data) {
        current = current->right; // Go right
      }
      else // Element matches current.element
        return true; // Element is found
    return false; // Element is not in the tree
  }

  boolean insert(T e) {
    if (isEmpty())
      // Create the node for e as the root;
      root = new Node<T>(0);
    else {
      // Locate the parent node
      parent = current = root;
      while (current != null)
        if (e < the value in current.element) {
          parent = current;       // Keep the parent
          current = current.left; // Go left
          }
        else if (e > the value in current.element) {
          parent = current;        // Keep the parent
          current = current.right; // Go right
          }
        else
          return false; // Duplicate node not inserted
        // Create a new node for e and attach it to parent
        return true; // Element inserted
      }
};

#endif // !_bTree_h_
