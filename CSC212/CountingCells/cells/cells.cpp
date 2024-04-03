#include "cells.h"
#include <sstream>
#include <iostream>

using namespace std;

cells::cells(){
    this->visited = false;
    this->filled = false;
    this->n = nullptr;
    this->e = nullptr;
    this->s = nullptr;
    this->w = nullptr;
}

cells::cells(bool filled){
    this->visited = false;
    this->filled = filled;
    this->n = nullptr;
    this->e = nullptr;
    this->s = nullptr;
    this->w = nullptr;
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
    // Set the origin
    ss >> temp;
    this->origin = new cells(temp);
    cells* tempCell = this->origin;
    // Take every value in the first line
    // cout << temp << " ";
    while(ss >> temp){
        // cout << temp << " ";
        tempCell->e = new cells(temp);
        cells* prev = tempCell;
        tempCell = tempCell->e;
        tempCell->w = prev;
    }
    // cout << endl;
    // Navigate temp cell back to left
    tempCell = this->origin;

    // While there are lines to read from the file
    while(getline(inFile, currLine)){
        istringstream ss(currLine);
        while(ss >> temp){
            // cout << temp << " ";
            tempCell->s = new cells(temp);
            cells* prevCell = tempCell;
            tempCell = tempCell->s;
            tempCell->n = prevCell;
            if(prevCell->w){
                prevCell = prevCell->w->s;
                prevCell->e = tempCell;
                tempCell->w = prevCell;
                prevCell = prevCell->n->e;
            }
            if(prevCell->e){
                tempCell = prevCell->e;
            }
        }
        // cout << endl;
        // Navigate back to the left
        while(tempCell->w){
            tempCell = tempCell->w;
        }
    }
    // Get the starting cell
    tempCell = this->origin;
    for(int i = 1; i < startingRow; i++){
        tempCell = tempCell->s;
    }
    for(int j = 1; j < startingCol; j++){
        tempCell = tempCell->e;
    }
    this->startingCell = tempCell;
    // Determine which conn type to use
    cout << connType(this->startingCell, conn) << endl;
}

// Method to check all cells in the grid
int grid::blobCount(cells* cell, int conn){
    if(!cell){
        return 0;
    }
    int bCount = 0;
    if(cell->filled && !cell->visited){
        bCount ++;
        connType(cell, conn);
    }
    cell->visited = true;
    if(cell->e == cell){
        return bCount;
    }
    if(cell->s = cell){
        return bCount;
    }
    bCount += blobCount(cell->e, conn);
    bCount += blobCount(cell->s, conn);
    return bCount;
}


int grid::connType(cells* cell, int conn){
    int blobSize = 0;
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
        // If the conn type is 8, go diagonal as well
        if(conn == 8){
            if(cell->n){
                blobSize += connType(cell->n->e, conn);
                blobSize += connType(cell->n->w, conn);
            }
            if(cell->s){
                blobSize += connType(cell->s->e, conn);
                blobSize += connType(cell->s->w, conn);
            }
        }
    }
    return blobSize;
}