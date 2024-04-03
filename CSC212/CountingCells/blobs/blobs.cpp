#include "blobs.h"
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

grid::grid(string fName, int rows, int cols, int conn){
    this->rows = rows;
    this->cols = cols;
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
    // Determine which conn type to use
    cout << blobCount(this->origin, conn) << endl;
}

// Method to check all cells in the grid
int grid::blobCount(cells* cell, int conn){
    int count = 0;
    // While the cell still exists
    while(cell){
        // While there are cells to the right
        while(cell->e){
            // cout << cell->filled << " ";
            // If the cell is filled and has not been visited yet, it is the start of a blob
            if(cell->filled && !cell->visited){
                connType(cell, conn);
                count++;
            }
            // Mark cell as visited to avoid re-visiting
            cell->visited = true;
            // Move right
            cell = cell->e;
        }
        // return all the way to the left
        while(cell->w){
            cell = cell->w;
        }
        // Move down to next row
        cell = cell->s;
        // cout << endl;
    }
    return count;
}


int grid::connType(cells* cell, int conn){
    int blobSize = 0;
    // If the current cell is a nullptr
    if(!cell){
        return 0;
    }
    // If the cell has been visisted, return 0
    else if(cell->visited){
        return 0;
    }
    cell->visited = true;
    // If the cell is filled
    if(cell->filled){
        // Increase the blob size by 1
        blobSize = 1;
        // add any connecting cells to the blob's size
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