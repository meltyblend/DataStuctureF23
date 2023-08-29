/*Create a class/struct.

Members:
MaxSize const = 10
Define an array that holds 10 items.
Count - indicates how many items are on the queue.
Front - where the front of the queue is in the array.
Back - Where the end of the queue is in the array.


Methods:
En-queue O(1)
- Accepts a number and adds to the end of the queue.
- If the queue is full emit an error indicating full.
De-queue O(1)
- Returns a number from the front of the queue.
- If the queueis empty, emit an error indicating the queueis empty.
IsEmpty
- Returns a boolean indicating if the queue is empty.
*Note that the front and back can wrap around the end of the array over time. */



#include <iostream>

using namespace std;

#define MaxSize 10 //  defining max size of the array

// implementing a class  for the Queue dataa structure
class Queue {
private:
    // Private data members/attributes  of the queue
    int front; //front signifies front of array,
    int rear; // rear - rear
    int count; // count: how many items are on the queue
    int array[MaxSize]; // array will take in max size of 10

public:
    // constructor Queue
    Queue() {      // assuming  when front and  rear = -1 the queue is empty.
        front = -1;
        rear = -1;
        count = 0;
    };

    // checks for whether the queue is empty or not
    bool IsEmpty() {
        return ( front  == -1 && rear == -1 );
    }
    // to  check if the queue is full
    bool IsFull() {
        if ( (rear + 1) % MaxSize == front ) {
            return true;
        } else {
            return false;
        }
    }

    // inserting elements at the rear of the queue
    void Enqueue( int n ) { // n is the number you want to insert
        cout << "Enqueue: " << n << " \n";

        if( IsFull() ) {
            cout << "Sorry queue is full \n";
            return;
        }

        if( IsEmpty() ) {
            front = rear = 0;
        } else {
            // calculating the new rear position
            rear = (rear + 1) %  MaxSize;
        }
        // inserting new item
        array[rear] = n;
        //update item count
        count++;
    }

    //  remove an element from the front of the queue
    void  Dequeue() {
        cout << "Dequeue \n";

        if( IsEmpty() ) {
            cout << "Sorry queue is empty \n";
            return;
        }
        else if ( front == rear ) {
            rear = front = -1;
        } else {
            // moving front
            front = (front + 1) % MaxSize;
            count--;
        }
    }

    // return element at front of queue
    int Front() {
        if( front == -1 ) { //checking if queue is empty first
            cout << "Cannot return front from empty queue \n";
            return -1;
        }
        return array[front];
    }

    // function that will print the coded information
    void Print() {
        if( IsEmpty() ) {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Queue: ";
        //finding number of elements within the queue
        int itemCount = (rear + MaxSize - front) % MaxSize + 1;

        for( int i = 0; i < itemCount; i++ ) {
            int index = (front + i)  % MaxSize;
            cout << array[index] << " ";
        }
        cout << "\n\n";

    }
};

int main() {
    Queue Q;
    Q.Enqueue(1); Q.Print();
    Q.Enqueue(2); Q.Print();
    Q.Enqueue(3); Q.Print();
    Q.Dequeue(); Q.Print();
    Q.Enqueue(4); Q.Print();
}
