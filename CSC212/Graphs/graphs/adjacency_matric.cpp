#include "adjacency_matrix.h"

AdjMatrix::AdjMatrix(){
    
}

void AdjMatrix::addEdge(int source, int dest, int weight){
    // Check if the starting node does not exist
    if(!(source < this->matrix.size())){
        // cout << "New Row" << endl;
        for(int i = this->matrix.size(); i < dest; i++){
            vector<int> temp(this->col, 0);
            this->matrix.push_back(temp);
            this->row++;
        }
    }
    // The starting node now exists
    // If the destination node doesn't exist
    if(!(dest < this->matrix[source].size())){
        // cout << "New Col" << endl;
        for(int i = this->matrix[source].size() - 1; i < dest; i++){
            // cout << "New column at row " << source << endl;
            this->matrix[source].push_back(0);
            this->col++;
        }
    }
    // Now the destination node exists
    this->matrix[source][dest] = weight;

    // Update all rows to have the column count
    for(vector<int>& col : this->matrix){
        if(col.size() < this->col){
            for(int i = col.size(); i < this->col; i++){
                col.push_back(0);
            }
        }
    }
    // Update to have same dimensions
    if(this->matrix.size() < this->col){
        // cout << "Update dimensions" << endl;
        vector<int> temp(this->col, 0);
        this->matrix.push_back(temp);
    }

    // printGraph();
    // cout << endl;
}

void AdjMatrix::printGraph(){
    for(vector<int> col : this->matrix){
        for(int i = 0; i < col.size(); i++){
            cout << col[i] << " ";
        }
        cout << endl;
    }
}

void AdjMatrix::outputGraph(string ofname){
    ofstream os(ofname);

    os << "digraph G {" << endl << endl;
    for(int i = 0; i < this->matrix.size(); i++){
        vector<int> col = this->matrix[i];
        for(int j = 0; j < col.size(); j++){
            if(col[j] != 0){
                os << "  " << i << " -> " << j << " [label=\"" << col[j] << "\"];" << endl;
            }
        }
    }
    os << endl;
    os << "}";

    os.close();
}