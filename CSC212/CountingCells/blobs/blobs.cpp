#include "blobs.h"
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

grid::grid(string fName, int rows, int cols, int conn){
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
    while(ss >> temp){
        tempCell->e = new cells(temp);
        cells* prev = tempCell;
        tempCell = tempCell->e;
        tempCell->w = prev;
    }
    // Navigate temp cell back to left
    tempCell = this->origin;

    // While there are lines to read from the file
    while(getline(inFile, currLine)){
        istringstream ss(currLine);
        while(ss >> temp){
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
        // Navigate back to the left
        while(tempCell->w){
            tempCell = tempCell->w;
        }
    }
    // Determine which conn type to use
    cout << blobCount(this->origin, conn) << endl;
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