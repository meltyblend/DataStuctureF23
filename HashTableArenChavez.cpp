/*Create a hash table class/struct.

Define an array that holds 27 elements.
Define a function called Hash(int)
-This function returns the modulo of that int by the size of the table (array).
Define an add function that takes an integer.
-This function takes the integer, determines the hash of that number by calling the above hash function, then adds it to the table using linear probing for collision resolution.
Define a function that looks up a value, it takes an integer, return -1 if the value is not in the table.
Create a main that allows the user to add and lookup items in the table.*/


#include <iostream>

using namespace std;

class HashTable{
private:
    //creating  array that holds 27 elements
    static const int table_size = 27;
    int table[table_size];

public:
    //initializing the array to -1
    HashTable(){
        for(int i =0; i < table_size; i++){
            table[i] = -1;
        }
    }

    // returning the modulo of the int by the size of the table(array)
    int Hash(int key){
        return key % table_size;
    }

    // adds a value to the Hash Table
    void Add(int value){
        int index = Hash(value);
        while(table[index] != -1){
            index = (index + 1) % table_size;
        }
        table[index] = value;
    }

    // searchs for the values index in the Hash Table
    int search(int value){
        int index = Hash(value);
        while(table[index] != -1){
            if(table[index] == value){
                return index;
            }
            index = (index + 1) % table_size;
        }
        return -1;
    }

};

int main() {

    HashTable myHashTable;

    // while statement to allow the user to choose what they want to do
    while(true){
        int choice;
        cout << "choose an operation: 1 - Add, 2 - Search, or 3 - quit:";
        cin >> choice;

        switch(choice){
            case 1:{
                int value;
                cout << "Enter a value to add to the table: ";
                cin >> value;
                myHashTable.Add(value);
                break;
            }
            case 2:{
                int value;
                cout << "enter a value to seatch: ";
                cin >> value;
                int index = myHashTable.search(value);
                // checking for if value is found;
                if(index != -1){
                    cout << "value found at index " << index << endl;
                } else {
                    cout << "value was not found." << endl;
                }
                break;
            }
            case 3: {
                return 0;
            }
            default:
                cout << "Invalid input, please select one of the following: 1 - Add, 2 - Search, or 3 - quit. " << endl;
        }
    }
}
