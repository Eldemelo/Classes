#include "cells.h"
#include <sstream>

using namespace std;

cells::cells(){
    this->filled = false;
    this->n = nullptr;
    this->ne = nullptr;
    this->e = nullptr;
    this->se = nullptr;
    this->s = nullptr;
    this->sw = nullptr;
    this->w = nullptr;
    this->nw = nullptr;
}

cells::cells(bool filled){
    this->filled = filled;
    this->n = nullptr;
    this->ne = nullptr;
    this->e = nullptr;
    this->se = nullptr;
    this->s = nullptr;
    this->sw = nullptr;
    this->w = nullptr;
    this->nw = nullptr;
}

grid::grid(){
    
}

grid::grid(string fName, int rows, int cols, int startingRow, int startingCol, int conn){
    ifstream inFile(fName);
    string currLine;
    // Get first line to set origin
    getline(inFile, currLine);
    istringstream ss(currLine);
    bool temp;
    cells* tempCell = this->origin;
    // Take every value in the first line
    for(int i = 1; i <= cols; i++){
        ss >> temp;
        // If it's the first value, it is the origin
        if(i == 1){
            this->origin = new cells(temp);
        }
        // Else it goes to the right
        else{
            tempCell->e = new cells(temp);
            cells* prevCell = tempCell;
            tempCell = tempCell->e;
            tempCell->w = prevCell;
        }
    }
    // Navigate temp cell back to left
    tempCell = this->origin;

    // While there are lines to read from the file
    while(getline(inFile, currLine)){
        istringstream ss(currLine);
        ss >> temp;
        for(int i = 1; i <= cols; i++){
            if(i == 1){
                tempCell->s = new cells(temp);
                cells* prevCell = tempCell;
                tempCell = tempCell->s;
                tempCell->ne = prevCell->e;
                prevCell = tempCell;
                tempCell = tempCell->ne;
                tempCell->sw = prevCell;
            }
            else{
                tempCell->s = new cells(temp);
                cells* prevCell = tempCell;
                tempCell = tempCell->s;
                tempCell->n = prevCell;
                tempCell->nw = prevCell->w;
                prevCell->w->se = tempCell;
                tempCell->w = prevCell->sw;
                prevCell->sw->e = tempCell;
                if(i < cols){
                    tempCell->ne = prevCell->e;
                    prevCell->e->sw = tempCell;
                }
            }
        }
    }
}