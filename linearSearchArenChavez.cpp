/*Search an un-ordered array an integers for a value, if the value is found return the index of its position in the array, if not found, return -1.*/

#include <iostream>

using namespace std;

// linearSearch algorithm, takes in the array, size of the array and your desired value
int linearSearch( int array[], int size, int desValue ) {

    for ( int i = 0; i < size; i++ ){
        if( desValue == array[i] ){
            return i;
        }
    }
    return -1;
}

int main() {
    //initializing array
    int array[] = { 42, 17, 73, 56,  29, 88, 12, 68,  5, 94 };
    int input;

    //getting user input to find there desired number from the set array
    cout << "Enter an integer greater than zero: " << endl;
    cin >> input;

    //calling our function linearSearch and passing  the variables we made in main to it
    int output = linearSearch(array,  10, input);

    // conditional to check whether the number you input is found or not
    if ( output >= 0 ){
        cout << "Your number: " << array[output] << " was found at index: " << output << endl;
    } else {
      cout << "Your number: " << input << " was not found." << endl;
    }

}
