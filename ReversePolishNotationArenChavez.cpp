
/*For this assignment, you are to write a program, which will calculate the results of Reverse Polish expressions that are provided by the user.

You must use a linked list to maintain the stack for this program (array implementations of the stack will not receive full credit).

You must handle the following situations (errors):
Too many operators (+ - / *)
Too many operands (doubles)
Division by zero

The program will take in a Polish expression that separates the operators and operands by a single space, and terminates the expression with an equals sign.

The program will continue to take and evaluate expressions until the user enters a zero (0) on a line by itself followed by a new line.

Your sample output should show the handling of all the error conditions as well as make use of all of the operators.*/

#include <iostream>
#include <sstream>
#include <string>
#include <stack>

using  namespace std;

class Stack{
private:
    //creating the linked list
    struct Node{
        double data;
        Node* next;
    };

    Node* top  = nullptr; // beginning of the stack
    double size = 0;

public:
    Stack(){
        top = nullptr;
        size = 0;
    }

    // Push function intakes one value of type int to pussh to the top of the stack
    void Push( double n ) {
        Node* temp = new Node;
        // setting up our temp variable
        temp->data = n;
        temp->next = top;
        top = temp;
        size++;
    }

    // Pop function will pop from the top of the stack in a LIFO fashion to satisfy O(1)
    double Pop() {
        Node* temp;

        if( IsEmpty() ) {
            cout << "No inputs were made\n";
            return 0;
        }
        temp = top;
        double val = temp->data;
        top = top->next; //updating the top to next node
        delete temp;   // deleting the old top node
        size--;
        return val;
    }

    // If top points to NULL then stack is empty
    bool IsEmpty() {
        return top == nullptr;
    }

    //getting size of the stack
    int Size() const {
        return size;
    }

};

//checks and gets operator inputted
bool getOperator( const string& token ){
    return token == "+" || token == "-" || token == "*" || token == "/";
}

// calculates all of the arithmetic based on the token in the inputted expression
double calculator( double a, double b, const string& op ){
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0){
            cout << "Error: division by zero." << endl;
            exit(1); //exiting if division is done by 0
        }
        return a / b;
    }
    return 0.0;
}

// Reverse Polish function
double RPN( const string& input ){
    Stack stack;
    istringstream iss(input);
    string token;

    int operandCount = 0;
    int operatorCount = 0;

    //breaking sting into smaller string or "tokenizing"
    while (iss >> token){
        if (!getOperator(token)){
            stack.Push(stod(token));
            operandCount++;
        } else {
            if (stack.Size() < 2){
                cout << "Error: too many operators." << endl;
                exit(1);
            }
            double b = stack.Pop();
            double a = stack.Pop();
            double result = calculator(a, b, token); //calculating inputs with the operator
            stack.Push(result); // pushing result back onto the stack
            operatorCount++;
        }
    }

    //checking for errors in the expression
    if (stack.Size() != 1) {
        cout << "Error: Too many operands" << endl;
        exit(1);
    }

    //returning final result
    return stack.Pop();
}


int main() {
    cout << "Reverse Polish Calculator" << endl;

    // looping prompt for convenience
    while (true) {
        string input;
        cout << "Enter an RPN expression (-1 to quit): ";
        getline(cin, input);

        // breaking the loop upon user entry
        if (input == "-1") {
            break;
        }

        if (input.empty()) {
            cout << "No input provided." << endl;
            continue; // skipping empty input lines
        }

        double result;
        if (input.back() == '=') {
            input.pop_back(); //removes the =
            result = RPN(input);
            cout << "Result: " << result << endl;
        } else {
            cout << "Result: " << RPN(input) << endl;
        }
    }

    return 0;
}

/* CODE OUTPUTS
 * C:\Users\pyuku\CLionProjects\Progam1ArenChavez\cmake-build-debug\Progam1ArenChavez.exe
Reverse Polish Calculator
Enter an RPN expression (-1 to quit): 10 15 + =
Result: 25

Enter an RPN expression (-1 to quit): 10 15 - =
Result: -5

Enter an RPN expression (-1 to quit): 2.5 3.5 + =
Result: 6

Enter an RPN expression (-1 to quit): 10 0 / =
Error: division by zero.

Enter an RPN expression (-1 to quit): 10 20 * / =
Error: too many operators.

Enter an RPN expression (-1 to quit): 12 20 30 / =
Error: Too many operands

Enter an RPN expression (-1 to quit): 100 10 50 25 / * - -2 / =
Result: -40

Enter an RPN expression (-1 to quit): -1
*/