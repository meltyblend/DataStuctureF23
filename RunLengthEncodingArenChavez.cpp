/*Build a run length encoding program.

Write a function that takes a string and returns the encoded string using run length encoding.

In main, prompt the user for a string.

Output the encoded string.

Output the compression rate.*/


#include <iostream>
#include<string>

using namespace std;

//function for Run Length Encoding
string RLE(string input){
    int n = input.length();
    int count = 1;
    string encoded_string = "";

    //iterating through the string and counting each time a character of that characters type is found
    for(int i = 0; i < n; i++){
        while(i < n - 1 && input[i] == input[i+1]){
            count++;
            i++;
        }
        encoded_string += input[i] + to_string(count);
        count = 1;
    }
    return encoded_string;
}

int main(){
    string user_input;
    cout << "Enter a string of random characters\n";
    cin >> user_input;

    string encoded_string = RLE(user_input);
    cout << "encoded string: " << encoded_string << endl;

    //calculating compression rate
    float original_size = user_input.size();
    float compressed_size = encoded_string.size();
    float compression_rate = static_cast<float>(original_size) / compressed_size;

    cout << "compression rate: " << compression_rate << "%" << endl;

    return 0;
}
