#include <iostream>     
#include <fstream>      
#include <vector>       
#include <unordered_map>
#include <string>       
#include <sstream>      
#include <list>         

using namespace std;

const int TABLESIZE = 100; // constant table size used for hashing

// Node class representing a key-value pair in the hash table
class Node {
public:
    int key;           // The key of the node
    string value;      // The value associated with the key
    Node* next;        // Pointer to the next node in the list (for chaining in hash table)

    // Constructor
    Node(int key, string value) : key(key), value(value), next(nullptr) {}
};

// HashTable class using a basic hash table with chaining
class HashTable{
private:
    int size;                           // Size of the hash table
    vector<list<Node*>> table;          // Vector of lists to store nodes (chaining)

    // Hash function to compute index for a given key
    int hash(int key){
        return key % size;
    }

public:
    // Constructor to initialize hash table with a given size
    HashTable(int initial_size) : size(initial_size), table(initial_size){}

    // Function to insert a key-value pair into the hash table
    void insertVariable(int key, const string& value){
        int index = hash(key);                      // Compute index using hash function
        Node* newNode = new Node(key, value);       // Create a new node
        table[index].push_back(newNode);            // Insert the node into the list at that index
    }

};

// Variable class representing a variable with a name and a value
class Variable{
public:
    string name;    // Name of the variable
    int value;      // Value of the variable

    // Constructor to initialize variable with name and value
    Variable(string name, int value) : name(name), value(value) {}
};

class BorgInterpreter{
private:
    // Stack of scopes, each scope is an unordered_map of variables hashed by their names
    vector<unordered_map<int, Variable>> scopes;

    // Function to compute a hash for a variable name
    int computeHash(string var_name){
        int sum = 0;
        for (int i = 0; i < var_name.size(); i++){
            sum += (var_name[i] * (i + 1));  // Sum of character codes times position
        }
        return sum % TABLESIZE;  
    }

public:
    // Function to execute a Borg program from a file
    void executeBorgProgram(const string& filename, HashTable& hashTable){
        ifstream infile(filename);   // Open the file
        string line;

        // Read the file line by line
        while (getline(infile, line)){
            istringstream iss(line);   // Create a string stream from the line
            string command;
            iss >> command;            // Read the command
            executeCommand(command, iss, hashTable);  // Execute the command
        }

        infile.close();  // Close the file
    }

private:
    // Function to execute a single command
    void executeCommand(const string& command, istringstream& iss, HashTable& hashTable){
        if (command == "START"){
            // Begin a new scope by pushing a new unordered_map onto the scopes stack
            scopes.push_back(unordered_map<int, Variable>());
        } else if (command == "FINISH"){
            // End the current scope by popping the top unordered_map off the scopes stack
            if (!scopes.empty()){
                scopes.pop_back();
            }
        } else if (command == "COM"){
            // Comment line, do nothing
        } else if (command == "VAR"){
            // Variable declaration

            string var_name, equal_sign;
            int value;
            iss >> var_name >> equal_sign >> value;  // Read variable name, '=', and value

            int hash = computeHash(var_name);        // Compute hash of variable name
            // Insert the variable into the current scope
            scopes.back().insert({hash, Variable(var_name, value)});
            // Also insert the variable into the hash table (not used in this code)
            hashTable.insertVariable(hash, var_name);

        } else if (command == "PRINT"){
            // Print command

            string var_name;
            iss >> var_name;           // Read variable name
            int hash = computeHash(var_name);  // Compute hash of variable name

            if(iss.peek() != EOF){
                // Additional operation specified after variable name

                string operation;
                int factor;
                iss >> operation >> factor;  // Read operation and factor

                bool variable_found = false;

                // Search for the variable in the scopes stack from innermost to outermost
                for(auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if(var_it != it->end()){
                        variable_found = true;

                        if(operation == "*"){
                            // Multiply variable's value by factor and print
                            cout << var_it->second.name << " * " << factor << " IS " << var_it->second.value * factor << endl;
                        } else {
                            // Unsupported operation
                            cout << "Unsupported operation" << endl;
                        }
                        break;
                    }
                }
                if(!variable_found){
                    // Variable not found in any scope
                    cout << var_name << " IS UNDEFINED" << endl;
                }
            } else {

                bool variable_found = false;

                // Search for the variable in the scopes stack from innermost to outermost
                for(auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if(var_it != it->end()){
                        variable_found = true;
                        // Print the variable's value
                        cout << var_it->second.name << " IS " << var_it->second.value << endl;
                        break;
                    }
                }
                if(!variable_found){
                    // Variable not found
                    cout << var_name << " IS UNDEFINED" << endl;
                }
            }

        } else {
            // Assignment or operation on a variable

            string var_name = command;   
            string operation;
            iss >> operation;            // Read the operation
            int hash = computeHash(var_name);  // Compute hash of variable name

            if (operation == "="){
                // Assignment operation

                int value;
                iss >> value;   // Read the value to assign

                bool variable_found = false;

                // Search for the variable in the scopes stack
                for (auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if (var_it != it->end()){
                        variable_found = true;
                        // Assign new value to the variable
                        var_it->second.value = value;
                        break;
                    }
                }
                if(!variable_found){
                    // Variable not found
                    cout << var_name << " IS UNDEFINED"<< endl;
                }

            } else if (operation == "++") {
                // Increment operation

                bool variable_found = false;

                // Search for the variable
                for (auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto varIt = it->find(hash);
                    if (varIt != it->end()) {
                        variable_found = true;
                        // Increment the variable's value
                        varIt->second.value++;
                        break;
                    }
                }
                if(!variable_found){
                    // Variable not found
                    cout << var_name << " IS UNDEFINED"<< endl;
                }

            } else if (operation == "--") {
                // Decrement operation

                bool variable_found = false;

                // Search for the variable
                for (auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if (var_it != it->end()) {
                        variable_found = true;
                        // Decrement the variable's value
                        var_it->second.value--;
                        break;
                    }
                }
                if(!variable_found){
                    // Variable not found
                    cout << var_name << " IS UNDEFINED"<< endl;
                }

            } else if (operation == "*") {
                // Multiply and print operation

                int factor;
                iss >> factor;  

                bool variable_found = false;

                // Search for the variable
                for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
                    auto var_it = it->find(hash);
                    if (var_it != it->end()) {
                        variable_found = true;
                        // Print the result of the multiplication
                        cout << var_it->second.name << " * " << factor << " IS " << var_it->second.value * factor << endl;
                        break;
                    }
                }
                if(!variable_found){
                    // Variable not found
                    cout << var_name << " IS UNDEFINED"<< endl;
                }
            }
        }
    }
};

int main() {
    HashTable hash_table(100);             // Create a hash table with size 100
    BorgInterpreter borg_interpreter;      // Create an instance of BorgInterpreter

    ifstream inputFile("borg.txt");        // Open the borg.txt file

    if (!inputFile.is_open()) {
        cerr << "Error, cannot open the input file." << endl;
        return 1;
    }

    int key;
    string value;

    // Read key-value pairs from the file and insert into the hash table
    // This loop assumes the file starts with key-value pairs
    while (inputFile >> key >> value) {
        hash_table.insertVariable(key, value);
    }

    inputFile.close();  // Close the input file

    // Execute the Borg program using the interpreter
    borg_interpreter.executeBorgProgram("borg.txt", hash_table);

    return 0;
}

/*OUTPUT
 *
 *
BORAMIR IS 25
LEGOLAS IS 101
GANDALF IS UNDEFINED
BORAMIR * 2 IS 52
GANDALF IS 49
BORAMIR IS 26
GANDALF IS UNDEFINED
LEGOLAS IS 1000
LEGOLAS IS 1000
LEGOLAS IS 999
 *
 *
 *
 *
 * */
