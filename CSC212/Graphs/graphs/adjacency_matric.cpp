#include "adjacency_matrix.h"

AdjMatrix::AdjMatrix(){
    
}

void AdjMatrix::addEdge(int source, int dest, int weight){
    // Check if the starting node does not exist
    if(!(source < matrix.size())){
        for(int i = matrix.size() - 1; i < dest; i++){
            vector<int> temp(this->col, 0);
            matrix.push_back(temp);
            this->row++;
        }
    }
    // The starting node now exists
    // If the destination node doesn't exist
    if(!(dest < matrix[source].size())){
        for(int i = matrix[source].size() - 1; i < dest; i++){
            // cout << "New column at row " << source << endl;
            matrix[source].push_back(0);
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
    for(vector<int> col : this->matrix){
        for(int i = 0; i < col.size(); i++){
            os << col[i] << " ";
        }
        os << endl;
    }
    os.close();
}