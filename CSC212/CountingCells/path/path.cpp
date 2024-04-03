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
    // cout << blobCount(this->origin) << endl;
}

pair<int, int> grid::findLowest(cells* cell){
    int lowestValue = cell->value;
    int lowestRow = 1;
    int lowestCol = 1;
    for(int i = 1; i <= this->rows; i++){
        for(int j = 1; j <= this->cols; j++){
            if(cell->value < lowestValue){
                lowestValue = cell->value;
                lowestRow = i;
                lowestCol = j;
            }
            cell = cell->e;
        }
        // Navigate back to the left
        while(cell->w){
            cell = cell->w;
        }
        cell = cell->s;
    }
}