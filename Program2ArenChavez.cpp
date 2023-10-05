/*Program Specification:
1. Read data for names and weights for 15 people from the console where there is a name on a line followed by a weight on the next line, like in names.txt.
2. Your program will build a list for the data maintained in ascending order based on both name and weight via a doubly linked list.
3. This dll will use one pointer to keep weights in sorted order, and use the other link to keep names on sorted order.
4. You need to build the list as you go maintaining this ordering, so at any time a print method was called it would print the related field in order.
 (This means nodes are added to the list in sorted order, elements are not added to the list followed by a sort called on the list.)*/

#include <iostream>
#include <string>

using namespace std;

//Node class
class Node {
public:
    Node* nodeName; //pointer to the name
    Node* nodeWeight; // pointer to the weight
    string name;
    int data;

    //constructor
    Node(string n, int x) : nodeName(nullptr), nodeWeight(nullptr), name(std::move(n)), data(x) {}
};

class DLL {
private:
    Node* headName;
    Node* headWeight;

public:
    DLL() : headName(nullptr), headWeight(nullptr) {}

    //function to insert a new Node into the DLL sorted by name
    void byName(string name, int data){
        Node* newNode = new Node(name, data);

        // Insertion at the beginning or in the middle
        if(headName == nullptr || headName->name >= name){
            // If the DLL is empty or new node comes before the current head,
            // insert the new node at the beginning.
            newNode->nodeName = headName; // Point the new node to the current head.
            headName = newNode; // Update the head to the new node, making it the new head.
        } else {
            // If the new node should be inserted in the middle or at the end,
            // we need to find the correct position while maintaining alphabetical order.

            Node* current = headName; // Start at the head of the list.

            while (current->nodeName && current->nodeName->name < name) {
                // Traverse the list until the next node's name is greater than or equal to the new name.
                current = current->nodeName;
            }

            // Insert the new node at the found position.
            // Connect the new node to the next node and update the current node's link.
            newNode->nodeName = current->nodeName;
            current->nodeName = newNode;
        }
    }

    //function to insert a new node in the class DLL by weight
    void byWeight(string name, int data){
        Node* newNode = new Node(name, data);

        // Insertion by weight
        if (headWeight == nullptr || headWeight->data >= data) {
            newNode->nodeWeight = headWeight;
            headWeight = newNode;
        } else {
            Node* current = headWeight;

            while (current->nodeWeight && current->nodeWeight->data < data) {
                current = current->nodeWeight;
            }
            newNode->nodeWeight = current->nodeWeight;
            current->nodeWeight = newNode;
        }
    }


    //prints names in alphabetical order
    void sortName(){
        Node* current = headName;

        cout << "Names sorted alphabetically: ";
        while (current) {
            cout << current->name << " - " << current->data;
            if(current->nodeName) {
                cout << ", ";
            }
            current = current->nodeName;
        }
        cout << "\n";
    }

    //prints weight in ascending order
    void sortWeight(){
        Node* current = headWeight;

        cout << "Weights in ascending order: ";
        while (current){
            cout << current->name << " - " << current->data;
            if (current->nodeWeight){
                cout << ", ";
            }
            current = current->nodeWeight;
        }
        cout << "\n";
    }
};

int main() {
    DLL input;
    string name;
    int data;

    cout<< "enter data or enter -1 for Name and Weight to quit." << "\n";

    //input loop to collect data until -1 is inputed
    while (true){
        cout << "Enter Name: ";
        cin >> name;

        if (name == "-1") {
            cout << "\n";
            break;
        }

        cout << "Enter Weight: ";
        cin >> data;

        if (data == -1){
            cout << "\n";
            break;
        }
        input.byName(name, data);
        input.byWeight(name,data);
    }

    input.sortName();
    input.sortWeight();

    return 0;
}
.
/*C:\Users\pyuku\CLionProjects\Program2ArenChavez\cmake-build-debug\Program2ArenChavez.exe
enter data or enter -1 for Name and Weight to quit.
Enter Name: Mark
Enter Weight: 150
Enter Name: Tina
Enter Weight: 115
Enter Name: Zach
Enter Weight: 55
Enter Name: Amy
Enter Weight: 140
Enter Name: Steve
Enter Weight: 220
Enter Name: Brian
Enter Weight: 250
Enter Name: Liz
Enter Weight: 125
Enter Name: Brian
Enter Weight: 220
Enter Name: Laura
Enter Weight: 115
Enter Name: Alex
Enter Weight: 175
Enter Name: Jason
Enter Weight: 210
Enter Name: Eric
Enter Weight: 175
Enter Name: Aaron
Enter Weight: 195
Enter Name: Kim
Enter Weight: 135
Enter Name: Brandon
Enter Weight: 78
Enter Name: -1

Names sorted alphabetically: Aaron - 195, Alex - 175, Amy - 140, Brandon - 78, Brian - 220, Brian - 250, Eric - 175, Jason - 210, Kim - 135, Laura - 115, Liz - 125, Mark - 150, Steve - 220, Tina - 115, Zach - 55
Weights in ascending order: Zach - 55, Brandon - 78, Laura - 115, Tina - 115, Liz - 125, Kim - 135, Amy - 140, Mark - 150, Eric - 175, Alex - 175, Aaron - 195, Jason - 210, Brian - 220, Steve - 220, Brian - 250
*/