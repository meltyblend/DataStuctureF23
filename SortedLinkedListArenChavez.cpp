/*Objective:  Create a sorted singly linked list of numbers based upon user input.

Program logic:
Ask for a number, add that number to the list in sorted position, print the list.
Repeat until they enter -1 for the number.*/

#include <iostream>

using namespace std;


class LinkedList {

private:
    // node structrure
    struct Node {

        int data;
        Node* next;

        // constructor
        Node(int data, Node *next) : data(data), next(next) {}
    };

    Node* head;

public:

    // initializing head member
    LinkedList() : head(nullptr) {}

    //using insertion sort
    void Insert( int x ){
        //dynamically allocating memory for a new Node with x val and nullptr pointer
        Node* newNode = new Node(x,  nullptr);

        // if the list is empty or the new element is less than or equal to the head insert the new element at the
        //beginning of the list
        if( !head || head->data >= x ){
            newNode->next = head; //pointer the new node to the current head
            head = newNode; //updating the head to the new node
        } else {
            //if list is not empty and the new element is greater than the head's daty
            // we need to find  the correctt position to insert the new element while maintaining sorted order
            Node* current = head; // starting at the head of the list
            // traversing the list to find the correct position to insert the new element
            while( current->next && current->next->data < x ){
                current = current->next; // moving to  the next node
            }
            // inserting  the new element between current  and  current->next
            newNode->next = current->next; // point the new node to the node after current
            current->next = newNode;       // update current to point to the new node
        }
    }

    //function to display the sorted link list
    void Display(){
        Node* current = head;


        while( current ) {
            cout << current->data << " "; //outputting  the data of the current node
            current = current->next;      // move to the next node in the list
        }
        cout << endl;
    };

    //destructor to free the previously allocated memory

    ~LinkedList() {
        // deleting all the previous nodes after the user enters -1
        while( head ) {
            Node* temp = head;
            head =  head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList L;
    int Input;

    while( true ) {
        cout << "Enter an integer (enter -1 to quit): ";
        cin >> Input;

        if( Input == -1 ) {
            cout << "\nList Cancelled";
            break; // exit when user enters  -1
        }
        L.Insert(Input);
        L.Display();
    }

    cout << "\nSorted linked List: ";
    L.Display();

    return 0;
}
