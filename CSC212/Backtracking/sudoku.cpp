#include "sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Sudoku::Sudoku() {
    for (unsigned int i = 0; i < this-> BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this-> BOARD_SIZE; j++) {
            this->board[i][j] = 0;
        }
    }
}

Sudoku::~Sudoku() {
    
}

Sudoku::Sudoku(string f_name) {
    // Generate a board from the give file
    ifstream inFile(f_name);
    string currLine, temp;
    int i = 0;
    while(getline(inFile, currLine)){
        stringstream currLineStream(currLine);
        int j = 0;
        while(currLineStream >> temp){
            board[i][j] = stoi(temp);
            j++;
        }
        i++;
    }
    inFile.close();
}

bool Sudoku::solve() {
    // 1) If we have filled the entire board,  return true
    // 2) For each digit 1-9:
        // if the digit can be place in this row, column, and cell
    for(unsigned int i = 0; i < this->BOARD_SIZE; i++){
        for(unsigned int j = 0; j < this->BOARD_SIZE; j++){
            if(this->board[i][j] == 0){
                for(int digit = 1; digit < 10; digit++){
                // If this digit can be placed at this index
                    if(is_valid(i, j, digit)){
                        // Place the digit here
                        this->board[i][j] = digit;
                        // If the recursive call returns true, return true
                        if(solve()){
                            return true;
                        }
                        // Remove number from current index 
                        // Backtrack
                        this->board[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    //     - Place the digit
    //         - Recurse to the next empty cell.
    //         - If that recursive call returns true
    //             - Return true
    //         - else
    //             - Try the next digit
    // 3) If none of the digits yielded a valid solution, backtrack

    return true;
}

// If this is an empty space & the given number does not exist in the same
// row, column, or box then it will return true.
bool Sudoku::is_valid(unsigned int row, unsigned int col, int num){
    return (this->board)[row][col] == 0
            && !check_row(row, num)
            && !check_col(col, num)
            && !check_box(row - row % 3, col - col % 3, num);
}

bool Sudoku::check_row(unsigned int row, unsigned int num){
    for(unsigned int i = 0; i < this->BOARD_SIZE; i++){
        if(this->board[row][i] == num){
            return true;
        }
    }
    return false;
}

bool Sudoku::check_col(unsigned int col, unsigned int num){
    for(unsigned int i = 0; i < this->BOARD_SIZE; i++){
        if(this->board[i][col] == num){
            return true;
        }
    }
    return false;
}

bool Sudoku::check_box(unsigned int boxStartRow, unsigned int boxStartCol, unsigned int num){
    // Check each index in the box and see if the number already exists
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[boxStartRow + i][boxStartCol + j] == num){
                return true;
            }
        }
    }
    return false;
}

void Sudoku::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            cout << (this->board)[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char * argv[])
{
    string f_name(argv[1]);

    Sudoku s(f_name);

    s.solve();

    s.display_board();

    return 0;
}