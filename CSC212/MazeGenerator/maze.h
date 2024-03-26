using namespace std;
#include <string>
#include <vector>

class maze{
private:
    int seed;
    int rows;
    int cols;
    string fileName;
public:
    maze(int seed, int rows, int cols, string fileName);
    void generateMaze();
    void generateMaze2();
    int determineWalls(int walls, char direction);
    void outputMazeFile(vector<vector<pair<int, bool>>> mazeGrid);
};