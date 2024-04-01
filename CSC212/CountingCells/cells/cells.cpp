#include "cells.h"
#include <sstream>
#include <iostream>

using namespace std;

cells::cells(){
    this->visited = false;
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
    this->visited = false;
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
            tempCell->s = new cells(temp);
            cells* prevCell = tempCell;
            tempCell = tempCell->s;
            tempCell->n = prevCell;
            if(prevCell->e){
                tempCell->ne = prevCell->e;
                prevCell->e->sw = tempCell;
            }
            if(prevCell->w){
                tempCell->w = prevCell->sw;
                prevCell->sw->e = tempCell;
                tempCell->nw = prevCell->w;
                prevCell->w->se = tempCell;
            }
            if(tempCell->ne){
                tempCell = tempCell->ne;
            }
        }
    }
    // Get the starting cell
    tempCell = this->origin;
    for(int i = 1; i <= startingRow; i++){
        cout << tempCell->filled << endl;
        tempCell = tempCell->s;
    }
    for(int j = 1; j <= startingCol; j++){
        cout << tempCell->filled << " ";
    }
    cout << "helloooo" << endl;
    this->startingCell = tempCell;
    // Determine which conn type to use
    cout << "Blob Size " << connType(this->startingCell, conn);
}
// Check all blobs connected to the north south east or west
int grid::connType(cells* cell, int conn){
    int blobSize = 0;
    if(conn == 4){
        if(!cell){
            return 0;
        }
        else if(cell->visited){
            return 0;
        }
        cell->visited = true;
        if(cell->filled){
            blobSize = 1;
            blobSize += connType(cell->n, conn);
            blobSize += connType(cell->s, conn);
            blobSize += connType(cell->e, conn);
            blobSize += connType(cell->w, conn);
        }
        return blobSize;
    }
    else{
        if(conn == 4){
        if(!cell){
            return 0;
        }
        else if(cell->visited){
            return 0;
        }
        cell->visited = true;
        if(cell->filled){
            blobSize = 1;
            blobSize += connType(cell->n, conn);
            blobSize += connType(cell->s, conn);
            blobSize += connType(cell->e, conn);
            blobSize += connType(cell->w, conn);
            blobSize += connType(cell->ne, conn);
            blobSize += connType(cell->nw, conn);
            blobSize += connType(cell->se, conn);
            blobSize += connType(cell->sw, conn);
            }
        }
    }
    return blobSize;
}