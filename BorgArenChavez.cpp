#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <list>

using namespace std;

const int TABLESIZE = 100;

class Node {
public:
    int key;
    string value;
    Node* next;

    Node(int key, string value) : key(key), value(value), next(nullptr) {}

};

class HashTable{
private:
    int size;
    vector<list<Node*>> table;

    int hash(int key){
        return key % size;
    }

public:
    HashTable(int initial_size) : size(initial_size), table(initial_size){}

    void insertVariable(int key, const string& value){
        int index = hash(key);
        Node* newNode = new Node(key, value);
        table[index].push_back(newNode);
    }

};

class Variable{
public:
    string name;
    int value;

    Variable(string name, int value) : name(name), value(value) {}
};

class BorgInterpreter{
private:
    vector<unordered_map<int, Variable>> scopes;

    int computeHash(string var_name){
        int sum = 0;
        for (int i = 0; i < var_name.size(); i++){
            sum += (var_name[i] * (i + 1));
        }
        return sum % TABLESIZE;
    }

public:
    void executeBorgProgram(const string& filename, HashTable& hashTable){
        ifstream infile(filename);
        string line;

        while (getline(infile, line)){
            istringstream iss(line);
            string command;
            iss >> command;
            executeCommand(command, iss, hashTable);
        }

        infile.close();
    }

private:
    void executeCommand(const string& command, istringstream& iss, HashTable& hashTable){
        if (command == "START"){
            scopes.push_back(unordered_map<int, Variable>());
        } else if (command == "FINISH"){
            if (!scopes.empty()){
                scopes.pop_back();
            }
        } else if (command == "COM"){
        } else if (command == "VAR"){

            string var_name, equal_sign;
            int value;
            iss >> var_name >> equal_sign >> value;

            int hash = computeHash(var_name);
            scopes.back().insert({hash, Variable(var_name, value)});
            hashTable.insertVariable(hash, var_name);

        } else if (command == "PRINT"){
            string var_name;
            iss >> var_name;
            int hash = computeHash(var_name);

            if(iss.peek() != EOF){
                string operation;
                int factor;
                iss >> operation >> factor;

                bool variable_found = false;

                for(auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if(var_it != it->end()){
                        variable_found = true;

                        if(operation == "*"){
                            cout << var_it->second.name << " * " << factor << " IS " << var_it->second.value * factor << endl;
                        } else {
                            cout << "Unsupported operation" << endl;
                        }
                        break;
                    }
                }
                if(!variable_found){
                    cout << var_name << " IS UNDEFINED" << endl;
                }
            } else {
                bool variable_found = false;

                for(auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if(var_it != it->end()){
                        variable_found = true;
                        cout << var_it->second.name << " IS " << var_it->second.value << endl;
                        break;
                    }
                }
                if(!variable_found){
                    cout << var_name << " IS UNDEFINED" << endl;
                }
            }

        } else {
            string var_name = command;
            string operation;
            iss >> operation;
            int hash = computeHash(var_name);

            if (operation == "="){
                int value;
                iss >> value;

                bool variable_found = false;

                for (auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if (var_it != it->end()){
                        variable_found = true;
                        var_it->second.value = value;
                        break;
                    }
                }
                if(!variable_found){
                    cout << var_name << " IS UNDEFINED"<< endl;
                }

            } else if (operation == "++") {
                bool variable_found = false;

                for (auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto varIt = it->find(hash);
                    if (varIt != it->end()) {
                        variable_found = true;
                        varIt->second.value++;
                        break;
                    }
                }
                if(!variable_found){
                    cout << var_name << " IS UNDEFINED"<< endl;
                }

            } else if (operation == "--") {
                bool variable_found = false;

                for (auto it = scopes.rbegin(); it != scopes.rend(); it++){
                    auto var_it = it->find(hash);
                    if (var_it != it->end()) {
                        variable_found = true;
                        var_it->second.value--;
                        break;
                    }
                }
                if(!variable_found){
                    cout << var_name << " IS UNDEFINED"<< endl;
                }

            } else if (operation == "*") {
                int factor;
                iss >> factor;

                bool variable_found = false;

                for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
                    auto var_it = it->find(hash);
                    if (var_it != it->end()) {
                        variable_found = true;
                        cout << var_it->second.name << " * " << factor << " IS " << var_it->second.value * factor << endl;
                        break;
                    }
                }
                if(!variable_found){
                    cout << var_name << " IS UNDEFINED"<< endl;
                }
            }
        }
    }
};

int main() {
    HashTable hash_table(100);
    BorgInterpreter borg_interpreter;

    ifstream inputFile("borg.txt");

    if (!inputFile.is_open()) {
        cerr << "Error, cannot open the input file." << endl;
        return 1;
    }

    int key;
    string value;

    while (inputFile >> key >> value) {
        hash_table.insertVariable(key, value);
    }

    inputFile.close();

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


