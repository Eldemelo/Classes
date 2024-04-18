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

    os << "digraph G {" << endl << endl;
    for(int i = 0; i < this->lst.size(); i++){
        list<pair<int, int>> col = this->lst[i];
        for(pair<int ,int> curr : col){
            os << "  " << i << " -> " << curr.first << " [label=\"" << curr.second << "\"];" << endl;
        }
    }
    os << endl;
    os << "}";

    os.close();
}

// Print even/odd weights graph
void AdjList::problem2(string ofname){
    ofstream os(ofname);

    os << "digraph G {" << endl << endl;
    for(int i = 0; i < this->lst.size(); i++){
        list<pair<int, int>> col = this->lst[i];
        for(pair<int ,int> curr : col){
            os << "  " << i << " -> " << curr.first << " [label=\"" << curr.second << "\"]";
            if(curr.second % 2){
                os << "[color=\"red\"];" << endl;
            }
            else{
                os << "[color=\"blue\"];" << endl;
            }
        }
    }
    os << endl;
    os << "}";

    os.close();
}

// Print edge position
void AdjList::problem3(string ofname){
    ofstream os(ofname);

    static string colors[] = {"green", "blue", "red", "purple"};

    os << "digraph G {" << endl << endl;
    for(int i = 0; i < this->lst.size(); i++){
        list<pair<int, int>> col = this->lst[i];
        int edge = 0;
        for(pair<int ,int> curr : col){
            os << "  " << i << " -> " << curr.first << " [label=\"" << curr.second << "\"]";
            os << "[color=\"" << colors[edge] << "\"];" << endl;
            edge = (edge + 1) % 4;
        }
    }
    os << endl;
    os << "}";

    os.close();
}

void AdjList::dfs(int startNode, ofstream &os, int depth = 0) {
    string colors[] = {"green", "blue", "red", "purple"};
    this->visited[startNode] = true;
    int edge = depth % 4;

    for(pair<int, int> curr : lst[startNode]){
        // Print the node
        (os) << "  " << startNode << " -> " << curr.first << " [label=\"" << curr.second << "\"]";
        (os) << "[color=\"" << colors[edge % 4] << "\"];" << endl;

        // Navigate down if not visited
        if (!visited[curr.first]){
            dfs(curr.first, os, depth + 1);
        }
    }
}

// Print distance from source graph
void AdjList::problem4(string ofname){
    for(int i = 0; i < this->lst.size(); i++){
        this->visited.push_back(false);
    }
    ofstream os(ofname);
    os << "digraph G {" << endl << endl;
    dfs(0, os);
    os << endl;
    os << "}";
    os.close();
}