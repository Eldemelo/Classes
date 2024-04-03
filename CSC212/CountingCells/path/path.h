#include <string>
#include <fstream>

using namespace std;

class cells{
    private:
        bool visited;
        int value;
        cells* n;
        cells* e;
        cells* s;
        cells* w;

        friend class grid;
    public:
    cells();
    cells(int value);
};

class grid{
    private:
        int rows, cols;
        cells* origin;
    public:
    grid();
    grid(string fName, int rows, int cols);
    pair<int, int> findLowest(cells* cell);
    pair<int, int> findHighest(cells* cell);
};