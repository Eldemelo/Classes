#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <iostream>
using namespace std;

class AdjList{
    private:
        vector<list<pair<int, int>>> lst;
        vector<bool> visited;
    public:
        AdjList();
        void addEdge(int source, int dest, int weight);
        void problem1(string ofname);
        void problem2(string ofname);
        void problem3(string ofname);
        void problem4(string ofname);
        void printGraph();
        void dfs(int startNode, ofstream &os, int depth);
};