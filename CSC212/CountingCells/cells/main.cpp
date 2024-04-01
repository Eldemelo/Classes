#include "cells.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    string fName = argv[1];
    int rows = stoi(argv[2]);
    int cols = stoi(argv[3]);
    int startRow = stoi(argv[4]);
    int startCol = stoi(argv[5]);
    int conn = stoi(argv[6]);

    grid cellGrid(fName, rows, cols, startRow, startCol, conn);
    
}