#pragma once
#include <string>
#include <fstream>
#include <tuple>

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
    tuple<int, int, int> findLowest(cells* cell);
    tuple<int, int, int> findHighest(cells* cell);
    bool hasPath(cells* cell, int lowest, int highest);
};