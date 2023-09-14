/*Create a class/struct for a node.
Create a class/struct for a list.

Members:
Top - a node that tracks the top of the stack
Count - indicates how many items are on the stack.

Methods:
Push O(1)
- Accepts a number and adds to the top of the stack.
Pop O(1)
- Returns a number from the top of the stack.
- If the stack is empty, emit an error indicating the stack is empty.
IsEmpty
- Returns a boolean indicating if the stack is empty.

Create and exercise a stack object in main.
*/


#include <iostream>

using namespace std;

class Stack {
private:

    // this is our link list structure.
    struct Node{
        int data;
        Node* next;
    };

    Node* top = nullptr; //when top is null stack is empty

    int count{0}; //indicates how many items are on the stack.

public:
    Stack(){
        top = nullptr;
        count = 0;
    }

    // Push function intakes one value of type int to push to the  top of the stack
    void Push( int n ) {
        cout << "\nPushing: " << n << " onto the stack\n";
        Node* temp = new Node;

        // setting up our temp variable
        temp->data = n;
        temp->next = top;
        top = temp;
        count++;
    }

    // Pop function will pop from the top of the stack in a LIFO fashion to satisfy O(1)
    void Pop() {
        cout << "\nPopping from the top of the stack\n";

        Node* temp;

        if( IsEmpty() ) {
            cout << "Sorry stack is empty\n";
            return;
        }
        temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    // If top points to NULL then stack is empty
    bool IsEmpty() {
        return top == nullptr;
    }

    // count  function to count  the elements in the stack
    int Count() {
        return count;

    }

    // print  function to show values and such
    void Print() {
        cout << "\nStack using last in first out (LIFO): \n";

        Node* temp = top;

        while ( temp != nullptr ) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    // destructor to release the previously allocated memory
    ~Stack() {
        cout << "\ndestructing the stack: ";
        while (!IsEmpty()) {
            Pop();
        }
    }

};
int main() {
    Stack S;

    S.Push(1);
    S.Push(2);
    S.Push(3);
    S.Push(4);
    S.Pop();

    cout << "Elements in the stack: " << S.Count() << endl;

    S.Print();

    return 0;
}
