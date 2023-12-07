#include <iostream>
#include <vector>
#include <list>

using namespace std;

// node class to store key-value pairs in the hashtable
class Node {
public:
    int key;
    string value;
    Node *next;

    //constructor
    Node(int key, string value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

// hashtable data structure with chaining
class HashTable {
private:
    int size;
    int count;
    vector<list<Node *>> table;

    // hash function
    int hash(int key) {
        return key % size;
    }

public:
    //constructor
    HashTable(int size) {
        this->size = size;
        this->count = 0;
        this->table = vector<list<Node *>>(size);
    }

    // add's a key value pair to the hash tabel
    void add(int key, string value) {
        int index = hash(key);
        Node *newNode = new Node(key, value);

        if (table[index].empty()) {
            table[index].push_front(newNode);
        } else {
            list<Node *>::iterator it = table[index].begin();
            while (it != table[index].end()) {
                if ((*it)->key == key) {
                    (*it)->value = value;
                    return;
                }
                it++;
            }
            table[index].push_back(newNode);
        }
    }

    //searches for for a value using the key as input
    string search(int key) {
        int index = hash(key);
        for (Node *node : table[index]) {
            if (node->key == key) {
                return node->value;
            }
        }
        return "key not found";
    }

    //removes a value using key as input
    string remove(int key) {
        int index = hash(key);
        for (Node *node : table[index]) {
            if (node->key == key) {
                string value = node->value;
                table[index].remove(node);
                delete node;
                return value;
            }
        }
        return "key not found";
    }
};

int main() {
    HashTable hashTable(10); //creating a hashtable with size 10

    int choice, key;
    std::string value;

    // menu for the user
    do {
        cout << "1. Add\n2. Lookup\n3. Delete\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            // adds a key-value pair to the hash tbale
            case 1:
                cout << "Enter key and value to add: ";
                cin >> key >> value;
                hashTable.add(key, value);
                break;
                // searches for a value using key as input
            case 2:
                cout << "Enter key to lookup: ";
                cin >> key;
                cout << "Value: " << hashTable.search(key) << endl;
                break;
                // deletes a value using the key as input
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                cout << "Deleted value: " << hashTable.remove(key) << endl;
                break;

            case 4:
                std::cout << "Exiting";
                break;
            default:
                std::cout << "Invalid. Please try again." << endl;
        }
    } while (choice != 4);
    return 0;
}
