/*Create a node class/struct.
Create a queue class/struct.

Members:
Node - a node that tracks the front of the queue.
Node - a node that tracks the end of the queue.
Count - indicates how many items are on the queue.

Methods:
En-queue
- Accepts a number and adds to the end of the queue.
De-queue
- Returns a number from the front of the queue.
- If the queueis empty, emit an error indicating the queueis empty.
IsEmpty
- Returns a boolean indicating if the queue is empty.*/


#include <iostream>

using namespace std;

// this struct holds our data type and a point that points to the next node in the linked list
class Queue{
private:
    struct Node {
        int data;
        Node* next;
    };

// these tro variables will store the address of the front and rear nodes
    Node* front = nullptr;
    Node* rear = nullptr;

// count to indicate how many items are in the queue
    int count{0};

public:

    Queue(){
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

// enqueue function to enqueue a variable of type INT
    void Enqueue( int n ) {
        cout << "\nEnqueue: " << n << "\n";

        Node* temp = new Node;
        temp->data = n;
        temp->next = nullptr;

        if( front == nullptr && rear == nullptr ) {
            front = rear = temp;
            return;
        } else {
            rear->next = temp;
            rear = temp;
        }

        count++;

    }

// dequeuing an integer from the linked list
    void Dequeue(){
        cout << "\nDequeueing the front element \n";

        Node* temp = front;

        if( front == nullptr ) {
            cout << "Sorry the queue is empty \n";
            return;
        }

        if( front == rear ) {
            front = rear = nullptr;
        } else {
            front = front->next;
        }

        delete temp;
        count--;

    }

    int Front(){
        if( front == nullptr ) {
            cout << "Sorry the queue is empty \n";
            return 0;
        }

        return front->data;

    }

    void Print() {
        Node* temp = front;
        while( temp != nullptr ) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << "\n";

    }

    bool IsEmpty() {
        return ( front == nullptr && rear == nullptr );

    }

    int Count() {
        if (IsEmpty()) {
            cout << "Queue is empty" << endl;
            return -1; // Return an error code or throw an exception
        }
        return count;
    }

};


int main() {
    Queue Q;

    cout << "\ncount: " << Q.Count() + 1 << endl;
}

