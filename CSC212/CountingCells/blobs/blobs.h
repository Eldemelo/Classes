#include <string>
#include <fstream>

using namespace std;

class cells{
    private:
        bool visited;
        bool filled;
        cells* n;
        cells* ne;
        cells* e;
        cells* se;
        cells* s;
        cells* sw;
        cells* w;
        cells* nw;

        friend class grid;
    public:
    cells();
    cells(bool filled);
};

class grid{
    private:
        cells* startingCell;
        cells* origin;
        int connType(cells* cell, int conn);
        int blobCount(cells* cell, int conn);
    public:
    grid();
    grid(string fName, int rows, int cols, int conn);
};