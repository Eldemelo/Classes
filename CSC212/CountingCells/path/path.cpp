#include "path.h"
#include <sstream>
#include <iostream>

using namespace std;

cells::cells(){
    this->visited = false;
    this->value = 0;
    this->n = nullptr;
    this->e = nullptr;
    this->s = nullptr;
    this->w = nullptr;
}

cells::cells(int value){
    this->visited = false;
    this->value = value;
    this->n = nullptr;
    this->e = nullptr;
    this->s = nullptr;
    this->w = nullptr;
}

grid::grid(){
    this->rows = 0;
    this->cols = 0;
    this->origin = nullptr;
}

grid::grid(string fName, int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    ifstream inFile(fName);
    string currLine;
    // Get first line to set origin
    getline(inFile, currLine);
    istringstream ss(currLine);
    int temp;
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
    tuple<int, int, int> lowest = findLowest(this->origin);
    cout << get<0>(lowest) << " " << get<1>(lowest) << " ";
    tuple<int, int, int> highest = findHighest(this->origin);
    cout << get<0>(highest) << " " << get<1>(highest) << " ";

    // Move a pointer to the starting lowest node's coordinates
    tempCell = this->origin;
    for(int row = 1; row < get<0>(lowest); row++){
        tempCell = tempCell->s;
    }
    for(int col = 1; col < get<1>(lowest); col++){
        tempCell = tempCell->e;
    }

    // Find if the grid has a path and print yes or no accordingly
    hasPath(tempCell, get<2>(lowest), get<2>(highest)) ? cout << "yes" : cout << "no";
}

// Recursive method to determine if the values have a path from lowest to highest
bool grid::hasPath(cells* cell, int lowest, int highest){
    // Base case
    if(!cell){
        return false;
    }
    if(cell->value == highest){
        return true;
    }
    cell->visited = true;
    bool pathFound = false;
    // Navigate each direction if possible
    if(cell->n && cell->n->value >= cell->value && !cell->n->visited){
        pathFound = hasPath(cell->n, cell->value, highest);
        if(pathFound){
            return true;
        }
    }
    if(cell->e && cell->e->value >= cell->value && !cell->e->visited){
        pathFound = hasPath(cell->e, cell->value, highest);
        if(pathFound){
            return true;
        }
    }
    if(cell->s && cell->s->value >= cell->value && !cell->s->visited){
        pathFound = hasPath(cell->s, cell->value, highest);
        if(pathFound){
            return true;
        }
    }
    if(cell->w && cell->w->value >= cell->value && !cell->w->visited){
        pathFound = hasPath(cell->w, cell->value, highest);
        if(pathFound){
            return true;
        }
    }
    return pathFound;
}


// Method to find the coordinates of the lowest value
tuple<int, int, int> grid::findLowest(cells* cell){
    int lowestValue = cell->value;
    int lowestRow = 1;
    int lowestCol = 1;
    for(int row = 1; row <= this->rows; row++){
        for(int col = 1; col <= this->cols; col++){
            if(cell->value < lowestValue){
                lowestValue = cell->value;
                lowestRow = row;
                lowestCol = col;
            }
            // Don't move east on the last column
            if(col != this->cols) {  
                cell = cell->e;
            }
        }
        // Only move west cols - 1 times
        for(int col = 1; col < this->cols; col++){
            cell = cell->w;
        }
        // Don't move south on the last row
        if(row != this->rows) {
            cell = cell->s;
        }
    }
    return make_tuple(lowestRow, lowestCol, lowestValue);
}

// Method to find the coordinates of the highest value
tuple<int, int, int> grid::findHighest(cells* cell){
    int highestValue = cell->value;
    int highestRow = 1;
    int highestCol = 1;
    for(int row = 1; row <= this->rows; row++){
        for(int col = 1; col <= this->cols; col++){
            if(cell->value > highestValue){
                highestValue = cell->value;
                highestRow = row;
                highestCol = col;
            }
            // Don't move east on the last column
            if(col != this->cols) {  
                cell = cell->e;
            }
        }
        // Only move west cols - 1 times
        for(int col = 1; col < this->cols; col++){
            cell = cell->w;
        }
        // Don't move south on the last row
        if(row != this->rows) {
            cell = cell->s;
        }
    }
    return make_tuple(highestRow, highestCol, highestValue);
}

