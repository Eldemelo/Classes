// Command line: $ g++ -std=c++11 -Wall main.cpp maze.cpp -o generator

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "maze.h"
using namespace std;

int main(int argc, char*argv[]){
    int seed = stoi(argv[1]);
    int rows = stoi(argv[2]);
    int cols = stoi(argv[3]);
    string fileName(argv[4]);
    maze Maze(seed, rows, cols, fileName);
    Maze.generateMaze2();
}