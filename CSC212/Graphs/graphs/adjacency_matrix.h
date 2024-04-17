#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class AdjMatrix{
    private:
        int row = 0;
        int col = 0;
        vector<vector<int>> matrix;
    public:
    AdjMatrix();
    void addEdge(int source, int dest, int weight);
    void printGraph();
    void outputGraph(string ofname);
};