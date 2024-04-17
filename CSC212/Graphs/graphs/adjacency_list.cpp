#include "adjacency_list.h"

AdjList::AdjList(){

}

void AdjList::addEdge(int source, int dest, int weight){
    // Check if the starting node does not exist:
    // Make it and insert the destination and weight as a pair
    if(!(source < this->lst.size())){
        pair<int, int> tempPair(dest, weight);
        list<pair<int, int>> temp;
        temp.push_back(tempPair);
        this->lst.push_back(temp);
    }
    // Otherwise the starting node already existed
    else{
        pair<int, int> tempPair(dest, weight);
        this->lst[source].push_back(tempPair);
    }
}

void AdjList::printGraph(){
    for(int start = 0; start < this->lst.size(); start++){
        list<pair<int, int>> temp = this->lst[start];

        for(pair<int, int> curr : temp){
            cout << start << " -> " << curr.first << " : " << curr.second << endl;
        }
    }
}

// Print default graph
void AdjList::problem1(string ofname){
    ofstream os(ofname);
    for(int start = 0; start < this->lst.size(); start++){
        list<pair<int, int>> temp = this->lst[start];

        for(pair<int, int> curr : temp){
            os << start << " -> " << curr.first << " : " << curr.second << endl;
        }
    }
    os.close();
}

// Print even/odd weights graph
void AdjList::problem2(string ofname){

}

// Print edge position
void AdjList::problem3(string ofname){

}

// Print distance from source graph
void AdjList::problem4(string ofname){

}