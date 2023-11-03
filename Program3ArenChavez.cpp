#include <iostream>

using namespace std;

//properties for the binary search tree
struct Node{
    string name;
    int data;
    Node* left = nullptr;
    Node* right = nullptr;

    //constructor
    Node(string user_name, int weight) : name(user_name), data(weight) {}
};

//Binary getSearch Tree Class
class Tree{
private:
    Node* root; //root node for the BST

    //inserting a node into tree
    void setInsert(Node* node, Node* insertNode) {
        if (insertNode->name < node->name) {
            if (node->left == nullptr) {
                node->left = insertNode;
            } else {
                setInsert(node->left, insertNode);
            }
        } else {
            if (insertNode->name > node->name) {
                if (node->right == nullptr) {
                    node->right = insertNode;
                } else {
                    setInsert(node->right, insertNode);
                }
            }
        }
    }
    //preorder traversal
    void setPreorder(Node* node){
        if(node == nullptr){
            return;
        } else {
            cout << node->name << " (" << node->data << "), ";
            setPreorder(node->left);
            setPreorder(node->right);
        }
    }

    //inorder traversal
    void setInorder(Node* node){
        if(node == nullptr){
            return;
        } else {
            setInorder(node->left);
            cout << node->name << " (" << node->data << "), ";
            setInorder(node->right);
        }
    }
    //postorder traversal
    void setPostorder(Node* node){
        if(node == nullptr){
            return;
        } else {
            setPostorder(node->left);
            setPostorder(node->right);
            cout << node->name << " (" << node->data << "), ";
        }
    }
    //calculating tree height
    int setTreeHeight(Node* node){
        if(node == nullptr){
            return 0;
        } else {
            int leftHeight = setTreeHeight(node->left);
            int rightHeight = setTreeHeight(node->right);
            if( leftHeight > rightHeight){
                return 1 + leftHeight;
            } else {
                return 1 + rightHeight;
            }
        }
    }
    //counting the number of leaf nodes on the tree
    int setLeafCount(Node* node){
        if(node == nullptr){
            return 0;
        }
        if(node->left == nullptr && node->right == nullptr){
            return 1;
        }
        int leftLeaf = setLeafCount(node->left);
        int rightLeaf = setLeafCount(node->right);
        return leftLeaf + rightLeaf;
    }
    //Searching for name and returning its weight
    int setSearch(Node* node, string user_name){
        if(node == nullptr){
            return -1;
        }
        if(node->name == user_name){
            return node->data;
        }
        if(user_name < node->name){
            return setSearch(node->left, user_name);
        } else {
            return setSearch(node->right, user_name);
        }
    }
    //finding loweset weight in the tree
    int setLowestHeight(Node* node){
        if(node->left == nullptr){
            return node->data;
        } else {
            return setLowestHeight(node->left);
        }
    }
    //finding name with the lowest valye in alphabetical order
    string setAlphabetical(Node* node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node->name;
    }

public:
    //constructor the BST
    Tree(){
        root = nullptr;
    }

    //inserting a  new node into the tree
    void Input(string user_name, int weight) {
        Node* newNode = new Node(user_name, weight);
        if (root == nullptr) {
            root = newNode;
        } else {
            setInsert(root, newNode);
        }
    }

    // the following are all public methods to get and print the results of specified function
    void getPreorder(){
        setPreorder(root);
        cout << endl;
    }

    void getInorder(){
        setInorder(root);
        cout << endl;
    }

    void getPostorder(){
        setPostorder(root);
        cout << endl;
    }

    int getTreeHeight(){
        return setTreeHeight(root);
    }

    int getLeafCount(){
        return setLeafCount(root);
    }

    int getSearch(string user_name){
        return setSearch(root, user_name);
    }

    int getLowestWeight(){
        if(root == nullptr){
            cout << "Tree is empty." << endl;
            return -1;
        }
        return setLowestHeight(root);
    }

    string getAlphabetical(){
        if(root == nullptr){
            cout << "The tree is empty." << endl;
            return "An error has occurred.";
        }
        return setAlphabetical(root);
    }


};

int main(){
    Tree myTree;
    string input_name;
    string search_name;
    string first_alpha = myTree.getAlphabetical();
    int weight;
    int lowest_weight = myTree.getLowestWeight();
    int search_result;

    //accepting user input to create the tree
    while (true) {
        cout << "Enter name (or -1 to exit): ";
        cin >> input_name;
        if (input_name == "-1") {
            cout << "Program exited." << endl;
            break;
        }

        cout << "Enter weight (or -1 to exit): ";
        cin >> weight;
        if (weight == -1) {
            cout << "Program exited." << endl;
            break;
        }

        myTree.Input(input_name, weight);
    }

    cout << "getPreorder Traversal: ";
    myTree.getPreorder();
    cout << "getInorder Traversal: ";
    myTree.getInorder();
    cout << "getPostorder Traversal: ";
    myTree.getPostorder();
    cout << "Tree height: " << myTree.getTreeHeight() << endl;
    cout << "Number of leaves: " << myTree.getLeafCount() << endl;


    cout << "getSearch for a name?: ";
    cin >> search_name;
    search_result = myTree.getSearch(search_name);
    if(search_result != -1){
        cout << "Name: " << search_name << ", Weight: " << search_result << endl;
    } else {
        cout << "No matching names for: " << search_name << endl;
    }

    if(lowest_weight != -1){
        cout << "Lowest Weight: " << lowest_weight << endl;
    }

    if(first_alpha != "An error occurred."){
        cout << "First name in alphabetical order: " << first_alpha << endl;
    }

    return 0;
}





//OUTPUT


/*
The tree is empty.
Tree is empty.
Enter name (or -1 to exit): Aren
        Enter weight (or -1 to exit): 110
Enter name (or -1 to exit): Arianne
        Enter weight (or -1 to exit): 100
Enter name (or -1 to exit): Eric
        Enter weight (or -1 to exit): 160
Enter name (or -1 to exit): John
        Enter weight (or -1 to exit): 220
Enter name (or -1 to exit): Bob
        Enter weight (or -1 to exit): 175
Enter name (or -1 to exit): Darren
        Enter weight (or -1 to exit): 111000
Enter name (or -1 to exit): Stinky
        Enter weight (or -1 to exit): 300
Enter name (or -1 to exit): Milk
        Enter weight (or -1 to exit): 278
Enter name (or -1 to exit): Mister
        Enter weight (or -1 to exit): 50
Enter name (or -1 to exit): Misses
        Enter weight (or -1 to exit): 49
Enter name (or -1 to exit): -1
Program exited.
getPreorder Traversal: Aren (110), Arianne (100), Eric (160), Bob (175), Darren (111000), John (220), Stinky (300), Milk (278), Mister (50), Misses (49),
getInorder Traversal: Aren (110), Arianne (100), Bob (175), Darren (111000), Eric (160), John (220), Milk (278), Misses (49), Mister (50), Stinky (300),
getPostorder Traversal: Darren (111000), Bob (175), Misses (49), Mister (50), Milk (278), Stinky (300), John (220), Eric (160), Arianne (100), Aren (110),
Tree height: 8
Number of leaves: 2
getSearch for a name?:
*/

