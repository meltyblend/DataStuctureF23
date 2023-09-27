/*Create a node class/struct
-Data field
-2 self referential pointers

Create a BST class/struct
-Node field
Methods:
Add (data)
-Adds the data to the tree in sorted order.
Print()
-Prints all the nodes using inorder traversal */


#include <iostream>

using namespace std;

//binary search tree nodes
class BSTnode{
public:
    int data;
    BSTnode *left;
    BSTnode *right;

    //constructor to initialize a BST node with data
    BSTnode(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

//binary search tree class
class BST {
private:
    BSTnode *root; //root node of bst

public:
    //constructor constructing empty bst
    BST(){
        root = nullptr;
    }

    //function to add a new element to the bst
    void add(int data){
        root = add(root, data);
    }

    //helper function to recursively add an element to the bst
    BSTnode *add(BSTnode *node, int data) {
        if (node == nullptr){
            return new BSTnode(data); // if the node is null create a new node with the given data
        }

        if (data <= node->data) { //if data is <= to the current node data, insert in the left subtree
            node->left = add(node->left, data);
        } else { //else add into the right subtree
            node->right = add(node->right, data);
        }
        return node;
    }
    // function to print the BST nodes in sorted order
    void print() {
        InOrderTrav(root);
    }
    //this helper function orders the elements int the ascendingly
    void InOrderTrav(BSTnode *node) {
        if (node == nullptr) {
            return;
        }
        InOrderTrav(node->left); //traversing left subtree
        cout << node->data << " "; //printing the current node's data
        InOrderTrav(node->right); // traversing the right subtree
    }
};

int main() {
    BST bst; //instantiating the object

    bst.add(10);
    bst.add(30);
    bst.add(70);
    bst.add(60);
    bst.add(90);
    bst.add(20);
    bst.add(50);
    bst.add(0);

    cout << " nodes in sorted order: ";
    bst.print();
    cout << endl;

}
