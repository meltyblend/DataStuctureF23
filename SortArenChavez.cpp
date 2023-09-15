/*Write a sort function that takes an array and sorts the values.
*/

/*
 * Bubble sort is terrible for large data sets
 * Big-O is O(n^2)
 * small data sets like the one I implemented its justafiable
 *
 * it sorts in pairs by comparing two pars of elements and swapping if they are not in order.
 * */
#include <iostream>

using namespace std;

int main() {

    cout << "BubbleSort\n";

    int array [5] = {5, 2, 9, 3, 7}; //initializing array

    //creating nested loops to compare two values of the array then sorting them
    for ( int i = 0; i < 4; i++ ){
        for ( int j = 0; j < 4 - i; j++ ){

            // this is where the sorting begins
            if( array[j] > array[j + 1] ){

                //comparing elementes within the array
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    // printing out the array using a range based for loop
    for(int i : array){
        cout << i << " ";
    }
    return 0;
}
