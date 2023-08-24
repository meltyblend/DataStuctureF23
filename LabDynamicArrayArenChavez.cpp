#include <iostream>

using namespace std;

int main() {
    int arraySize;

    // prompting user to enter a number that will create an array of that size
    cout <<  "\nEnter a number to create an array of that size." << endl;
    cin >> arraySize;

    // creating the array depending on the user input
    int array[arraySize];
    int n{0};
    int count{0};

    for ( int i = 0; i < arraySize; i++ )
    {
        cout << "\nEnter a number to add to the array, or enter -1 to exit: " << endl;
        cin >> n;
        // if statement to stop when ever user asks to stop
        if ( n == - 1 )
        {
            cout << "\nno more numbers can be entered.";
            break;
        } else {
            array[i] = n;
            count++;
        }
    }

    cout << "\nThese are the numbers you entered: \n" << endl;

    for ( int i = 0; i < count; i++ )
    {
        cout << array[i] << " ";
    }

    return 0;
}
