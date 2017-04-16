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
    Node<T>* root ;
 
    int countLeaves(Node<T>* node){
        if( node == NULL )
          return 0;
        if( node->left == NULL && node->right == NULL ) {
          return 1;
        } else {
          return countLeaves(node->left) + countLeaves(node->right);
        }
    }
    
    int getWidth(int level, Node<T>* root) {
      if(root == NULL)
        return 0;
      if(level == 1)
        return 1;
      else if (level > 1)
        return getWidth(level-1, root->left) + getWidth(level-1, root->right);
    }
    
    int height(Node<T>* node) {
        if (node==NULL)
         return 0;
        else {
         /* compute the height of each subtree */
         int lHeight = height(node->left);
         int rHeight = height(node->right);
         /* use the larger one */
        return (lHeight > rHeight)? (lHeight+1): (rHeight+1);
       }
    }

    void printGivenLevel(Node<T>* root, int level) {
        if (root == NULL)
            return;
        if (level == 1)
            cout << root->data << " ";
        else if (level > 1) {
            printGivenLevel(root->left, level-1);
            printGivenLevel(root->right, level-1);
        }
    }
    
public:
    
    BinaryTree(Node<T>* r = 0) : root(r) {};

    void travers() {
	norder(root);
	cout << endl;
	preorder(root);
    }

    void inorder(Node<T>* root) {
	if (root == NULL) return;
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
	}

    void preorder(Node<T>* root) {
	if (root == NULL) return;
	    cout << root->data << " ";
	    preorder(root->left);
            preorder(root->right);
	}
	
    bool isEmpty() { return root == NULL; }

    bool search(T element) {
        Node<T>* current = root;
        while (current != NULL)
        if (element < current->data) {
            current = current->left;
        }
        else if (element > current->data) {
            current = current->right;
        }
        else          
            return true; 
        return false; 
    } 

    bool insert(T e) {
        if (isEmpty())
            root = new Node<T>(0);
        else {
          Node<T>* parent = root;
          Node<T>* current = root;

         while (current != NULL)
          if (e < current->data) {
            parent = current;       // Keep the parent
            current = current->left; // Go left
            }
          else if (e > current->data) {
            parent = current;        // Keep the parent
            current = current->right; // Go right
          }
          else
            return false; // Duplicate node not inserted
          Node<T>* element = new Node<T>(e);
          if (e < parent->data) {
              parent->left = element;  
            }
          else{
              parent->right = element;  
            }
          return true; // Element inserted
        }
    }
    
    bool drop(T e) {
        // Locate the node to be deleted and also locate its parent node
        Node<T>* parent = NULL;
        Node<T>* current = root;
        while (current != NULL) {
            if (e < current->data) {
               parent = current;
               current = current->left;
            }
            else if (e > current->data) {
                parent = current;
                current = current->right;
            }
            else
                break; // Element is in the tree pointed at by current
        }
        if (current == NULL)
            return false; // Element is not in the tree
        // Case 1: current has no left child
        if (current->left == NULL) {
            // Connect the parent with the right child of the current node
            if (parent == NULL) {
                root = current->right;
            }
            else {
                if (e < parent->data)
                   parent->left = current->right;
                else
                   parent->right = current->right;
            }
            delete current;
        }
        // Case 2: The current node has a left child.
        else {
            // Locate the rightmost node in the left subtree of
            // the current node and also its parent.
            Node<T>* parentOfRightMost = current;
            Node<T>* rightMost = current->left;
            while (rightMost->right != NULL) {
                parentOfRightMost = rightMost;
                rightMost = rightMost->right; // Keep going to the right
            }
            // Replace the element in current by the element in rightMost
            current->data = rightMost->data;
            // Eliminate rightmost node            
            if (parentOfRightMost->right == rightMost)
                parentOfRightMost->right = rightMost->left;
            else
                // Special case: parentOfRightMost == current
                parentOfRightMost->left = rightMost->left;
            delete rightMost;
        }
        return true; // Element deleted successfully
    }
    
    int height() {
        height(root);
    }
    
    int getMaxWidth() {
      int maxWidth = 0; 
      for(int i = 1; i <= height(); ++i) {
          int w = getWidth(i);
          if( w > maxWidth ) maxWidth = w; 
      }
      return maxWidth;
    }
  
    int getWidth(int level) {
        getWidth(level, root);
    }
    
    int countLeaves(){
       countLeaves(root);
    }
  
    void printLevelOrder() {
        for(int i = 1; i <= height(); ++i)
            printGivenLevel(root, i);
    }
    
};

#endif // !_bTree_h_