#include "maze.h"
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <iostream>
using namespace std;


maze::maze(int seed, int rows, int cols, string fileName){
    this->seed = seed;
    this->rows = rows;
    this->cols = cols;
    this->fileName = fileName;
}

// Function to output generated maze to a file
void maze::outputMazeFile(vector<vector<pair<int, bool>>> mazeGrid){
    // Open file for writing;
    ofstream outputFile(this->fileName);
    if(!outputFile.is_open()){
        // cout << "error";
    }
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            outputFile << mazeGrid[i][j].first << " ";
        }
        outputFile << endl;
    }
}

// Function to generate maze
// Down then across
void maze::generateMaze2(){
    srand(this->seed);
    vector<vector<pair<int, bool>>> mazeGrid;
    vector<pair<int, int>> neighbors;
    vector<pair<int, int>> savedCoords;
    pair<int, int> current;
    // Initialize array with values
    for(int i = 0; i < this->rows; i++){
        vector<pair<int, bool>> currentRow;
        for(int j = 0; j < this->cols; j++){
            // Create a row
            currentRow.push_back(make_pair(15, false));
        }
        mazeGrid.push_back(currentRow);
    }
    // Initialize start and end of maze
    mazeGrid[0][0] = make_pair(mazeGrid[0][0].first - 8, true);
    mazeGrid[rows-1][cols-1] = make_pair(mazeGrid[rows-1][cols-1].first - 4, false);
    // Insert cell 0,0 at the end of savedCoords
    savedCoords.push_back(make_pair(0,0));
    int count = 0;
    while(savedCoords.empty() != true){
        cout << endl;
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->cols; j++){
                cout << mazeGrid[i][j].first << ", ";
            }
            cout << endl;
        }
        // Assign last val of savedCoords to current and remove it
        current = savedCoords.back();
        savedCoords.pop_back();
        // Check all neighbors and appends them to the neighbors array
        neighbors.clear();
        // To the north
        if(current.first - 1 >= 0){
            if (mazeGrid[current.first - 1][current.second].second == false){
                neighbors.push_back(make_pair(current.first - 1, current.second));
            }
        }
        // To the south
        if(current.first + 1 < rows){
            if (mazeGrid[current.first + 1][current.second].second == false){
                neighbors.push_back(make_pair(current.first + 1, current.second));
            }
        }
        // To the east
        if(current.second + 1 < cols){
            if(mazeGrid[current.first][current.second + 1].second == false){
                neighbors.push_back(make_pair(current.first, current.second + 1));
            }
        }
        // To the west
        if(current.second - 1 >= 0){
            if(mazeGrid[current.first][current.second - 1].second == false){
                neighbors.push_back(make_pair(current.first, current.second - 1));
            }
        }
        if(neighbors.size() > 0){
            savedCoords.push_back(current);
            int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
            pair<int, int> neigh = neighbors[idx];
            // Remove walls between current and neighbor
            // Move north
            if (neigh.first == current.first - 1){
                mazeGrid[current.first][current.second] = make_pair(mazeGrid[current.first][current.second].first - 8, true);
                mazeGrid[neigh.first][neigh.second] = make_pair(mazeGrid[neigh.first][neigh.second].first - 4, true);
            }
            // Move south
            if(neigh.first == current.first + 1){
                mazeGrid[current.first][current.second] = make_pair(mazeGrid[current.first][current.second].first - 4, true);
                mazeGrid[neigh.first][neigh.second] = make_pair(mazeGrid[neigh.first][neigh.second].first - 8, true);
            }
            // Move East
            if(neigh.second == current.second + 1){
                mazeGrid[current.first][current.second] = make_pair(mazeGrid[current.first][current.second].first - 2, true);
                mazeGrid[neigh.first][neigh.second] = make_pair(mazeGrid[neigh.first][neigh.second].first - 1, true);
            }
            // Move West
            if(neigh.second == current.second - 1){
                mazeGrid[current.first][current.second] = make_pair(mazeGrid[current.first][current.second].first - 1, true);
                mazeGrid[neigh.first][neigh.second] = make_pair(mazeGrid[neigh.first][neigh.second].first - 2, true);
            }
            // Insert neigh at the end of savedCoords
            savedCoords.push_back(neigh);
        }
    }outputMazeFile(mazeGrid);
}