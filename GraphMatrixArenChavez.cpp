#include <iostream>
#include <vector>
#include <string>

using namespace std;

class adjMatrix {
private:
    int num_vertices;
    vector<string> vertex_labels;
    vector<vector<int>> matrix;

public:
    //constructor
    adjMatrix(int num_vertices) : num_vertices(num_vertices), matrix(num_vertices, vector<int>(num_vertices, 0)){
        vertex_labels.resize(num_vertices);
    }

    void addEdge(int row, int col) {
        if(row >= 0 && row < num_vertices && col >= 0 && col < num_vertices){
            matrix[row][col] = 1;
            cout << "Added edge: " << vertex_labels[row] << " -> " << vertex_labels[col] << endl;
        } else {
            cout << "Invalid entry." << endl;
        }
    }

    void addLabel(const string& label, int vertex_index){
        if(vertex_index >= 0 && vertex_index < num_vertices){
            vertex_labels[vertex_index] = label;
        } else {
            cout << "Invalid index, cannot add label." << endl;
        }
    }

    void printEdge(){
        bool last_edge = true;

        cout << "Your edges are: ";
        for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j ++){
                if(matrix[i][j] == 1){
                    if(!last_edge){
                        cout << ", ";
                    }
                    cout << vertex_labels[i] << vertex_labels[j];
                    last_edge = false;
                }
            }
        }
        cout << endl;
    }

};

int main() {
    int num_vertices;
    string vertex_label;
    string user_input;

    //intialzing size of graph
    cout << "How many vertices?: ";
    cin >> num_vertices;

    adjMatrix myGraph(num_vertices);

    //user input to enter labels for the graph
    for(int i = 0; i < num_vertices; i++){
        cout << "What is the label for vertex " << i + 1 << "?: ";
        cin >> vertex_label;
        myGraph.addLabel(vertex_label, i);
    }

    cin.ignore();

    cout << "Define an edge by listing a pair of vertices, i.e. (A B, or -1 to stop)" << endl;
    while(true){
        getline(cin, user_input);
        if(user_input == "-1"){
            break;
        } else if (user_input.length() == 3) {
            int row = user_input[0] - 'A';
            int col = user_input[2] - 'A';
            myGraph.addEdge(row,col);
        } else {
            cout << "Invalid entry." << endl;
        }
    }

    myGraph.printEdge();
    return 0;
}