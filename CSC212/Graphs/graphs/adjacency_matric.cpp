#include "adjacency_matrix.h"

AdjMatrix::AdjMatrix(){
    
}

AdjMatrix::AdjMatrix(string ifname){
    ifstream inFile(ifname);
    string line;
    // While there are lines to read
    while(getline(inFile, line)){
        int start, end, weight;
        istringstream ss(line);
        ss >> start;
        ss >> end;
        ss >> weight;
        // Check if the starting node does not exist
        if(!(start <= matrix.size() - 1)){
            vector<int> temp(1, 0);
            this->matrix.push_back(temp);
            this->row++;
        }
        // The starting node now exists
        // If the destination node doesn't exist
        if(!(end > matrix[start].size() - 1)){
            for(int i = matrix[start].size() - 1; i < end; i++){
                matrix[start].push_back(0);
                this->col++;
            }
        }
        // Now the destination node exists
        matrix[start][end] = weight;
    }
    // Update all rows to have the column count
}

void AdjMatrix::addEdge(int source, int dest, int weight){
    
}

void AdjMatrix::printGraph(){

}

void AdjMatrix::outputGraph(string ofname){

}