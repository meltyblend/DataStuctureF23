/*Read a sentence from the console.
Break the sentence into words using the space character as a delimiter.
Iterate over each word, if the word is a numeric value then print its value doubled, otherwise print out the word, with each output on its own line.


Sample Run:
Sentence: Hello world, there are 3.5 items.


Output:
Hello
world,
there
are
7
items.*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {

    //user input prompt
    string input;
    cout << "Enter a sentence" << endl;
    getline( cin,  input);//reads the line of text from the console and stores it in input
    cout << "\n";

    //isstream creation to parse the sentence.
    istringstream isso( input );
    string word;

    // loop to break down each word individually with a space delimiter
    while ( getline(isso, word, ' ') ) {
        bool isNum = true;

        double numVal;
        // taking input as a double
        istringstream wordStream( word );
        if ( !(wordStream >> numVal )) {
            isNum = false;
        }

        //printing the input num by 2 as desired
        if ( isNum ) {
            cout << numVal * 2 << endl;
        } else {
            //  printing  the words back
            cout << word << endl;
        }
    }

    return 0;
}
