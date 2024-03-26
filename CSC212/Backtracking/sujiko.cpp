#include "sujiko.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

Sujiko::Sujiko() {

}

Sujiko::Sujiko(string fname) {
    // Read 4 sum values from file
    // Read file & create board
    ifstream inFile(fname);
    // If the file is open
    if(inFile.is_open()){
        string currLine, temp;
        // Read the first line
        getline(inFile, currLine);
        istringstream currStringStream(currLine);
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                currStringStream >> temp;
                nums[i][j] = stoi(temp);
            }
        }
        for(int i = 0; i < 3; i++){
            getline(inFile, currLine);
            istringstream currStringStream(currLine);
            for(int j = 0; j < 3; j++){
                currStringStream >> temp;
                board[i][j] = stoi(temp);
            }
        }
    }
    inFile.close();
}

Sujiko::~Sujiko() {
    
}

// Helper function to determine if the board is complete
bool Sujiko::is_valid(unsigned int row, unsigned int col, unsigned int num){
    
    for(unsigned int i = 0; i < this-> BOARD_SIZE; i++){
        if(this-> board[row][i] == num || this-> board[i][col] == num){
            return false;
        }
    }

    unsigned int subgridStartRow = row - row % 3;
    unsigned int subgridStartCol = col - col % 3;
    
    for(unsigned int i = 0; i < 3; i++){
        for(unsigned int j = 0; j < 3; j++){
            if (this-> board[subgridStartRow + i][subgridStartCol + j] == num){
                return false;
            }
        } 
    }
    return true;
}

bool Sujiko::solve(unsigned int cell){
    // If we placed a number succesfully on every cell, we did it!
    if (cell == 9) {
        if (board[0][0] + board[0][1] + board[1][0] + board[1][1] == nums[0][0]
        && board[0][1] + board[0][2] + board[1][1] + board[1][2] == nums[0][1]
        && board[1][0] + board[1][1] + board[2][0] + board[2][1] == nums[1][0]
        && board[1][1] + board[1][2] + board[2][1] + board[2][2] == nums[1][1]) {
            return true;
        }
        return false;
    }
    
    unsigned int row = cell / BOARD_SIZE;
    unsigned int col = cell % BOARD_SIZE;

    if (board[row][col] == EMPTY) {
        for (unsigned int num = 1; num <= 9; num++) {
            if (is_valid(row,col,num)) {
                this->board[row][col] = num;
                if (solve(cell+1)) {
                    return true;
                }
                this->board[row][col] = EMPTY;
            }
        }
    return false;
    }
    return solve(cell+1);
}

void Sujiko::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            cout << this->board[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char * argv[])
{
    Sujiko s(argv[1]);

    s.solve(0);

    s.display_board();

    return 0;
}
