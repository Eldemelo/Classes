#include "adjacency_matrix.h"
#include "adjacency_list.h"

using namespace std;

void adjacency_matrix(string ifname);
void adjacency_list(int mode, string ifname);

// Mode
// 0: Adjacency Matrix
// 1: Adjacency List
int main(int argc, char* argv[]){
    int mode = stoi(argv[2]);

    if(mode == 0){
        adjacency_matrix(argv[1]);
    }else{
        adjacency_list(mode, argv[1]);
    }
}

void adjacency_matrix(string ifname){
    AdjMatrix mat;
    ifstream ifs(ifname);
    string ofname = ifname.substr(0, ifname.rfind('.')) + "_output_0.dot";

    string line;

    int source;
    int dest;
    int weight;

    while(getline(ifs, line)){
        stringstream ss(line);
        ss >> source >> dest >> weight;
        mat.addEdge(source, dest, weight);
    }

    mat.printGraph();
    mat.outputGraph(ofname);
}

void adjacency_list(int mode, string ifname){
    AdjList lst;
    ifstream ifs(ifname);
    string ofname = ifname.substr(0, ifname.rfind('.')) + "_output_" + to_string(mode) + ".dot";
    string line;

    cout << ifname << endl;
    cout << ofname << endl;

    int source;
    int dest;
    int weight;

    while(getline(ifs, line)){
        stringstream ss(line);
        ss >> source >> dest >> weight;
        lst.addEdge(source, dest, weight);

    }

    lst.printGraph();
    if(mode == 1){
        lst.problem1(ofname);
    }else if(mode == 2){
        lst.problem2(ofname);
    }else if(mode == 3){
        lst.problem3(ofname);
    }else{
        lst.problem4(ofname);
    }

}