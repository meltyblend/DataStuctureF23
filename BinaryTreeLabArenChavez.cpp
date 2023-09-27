/*Create a binary tree class.

-Data array field (private)
-Count field
Add Function(data)
-The add method takes a data point, add it to the count position in the array then increases the count.
-Print Function
Preorder(int)
-Recursive method that prints all the nodes in a VLR pattern.
(Remember 2i + 1 & 2i + 2)*/

#include <iostream>
#include <vector>

using namespace std;

class BinaryTree {
private:
    //vector to store the binary tree data
    vector<int> data;
    int count;

public:
    //constructor and initializing thcount to 0
    BinaryTree() : count(0) {}

    void add(int data) {
        if (count < this->data.size()) {
            // if there is space in the vector overwrite the exisitng element
            this->data[count] = data;
        } else {
            //if no space add an element to the end of vector
            this->data.push_back(data);
        }
        count++;
    }

    void preorder(int i = 0 ) {
        if (i >= count) {
            return; // base case if index is out of bound
        }

        cout << data[i] << " ";
        //recursive trav left side of tree
        preorder(2 * i + 1);
        //recursive trav right side of tree
        preorder(2 * i + 2);
    }
};

int main(){
    BinaryTree tree;

    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);

    cout << "Preorder Traversal: ";
    tree.preorder();
    cout << std::endl;

    return 0;
}