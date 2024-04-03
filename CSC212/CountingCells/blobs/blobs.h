#include <string>
#include <fstream>

using namespace std;

class cells{
    private:
        bool visited;
        bool filled;
        cells* n;
        cells* e;
        cells* s;
        cells* w;

        friend class grid;
    public:
    cells();
    cells(bool filled);
};

class grid{
    private:
        int rows;
        int cols;
        cells* startingCell;
        cells* origin;
        int connType(cells* cell, int conn);
        int blobCount(cells* cell, int conn);
    public:
    grid();
    grid(string fName, int rows, int cols, int conn);
};