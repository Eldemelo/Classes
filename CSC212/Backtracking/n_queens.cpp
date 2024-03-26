#include "n_queens.h"

using namespace std;

NQueens::NQueens(){
    this->board_size = 0;
    this->board = nullptr;
}

NQueens::~NQueens(){
    delete this->board;
}

NQueens::NQueens(unsigned int n){
    this->board_size = n;

    board = new vector<vector<unsigned int >>(n, vector<unsigned int>(n));
}

bool NQueens::solve_rec(int col){
    //If all queens are placed then return true
    if(col == this->board_size){
        return true;
    }
    // Attempt to place a Queen in every row in
    // this column, one at a time.
    for(int i = 0; i < this->board_size; i++){
        // Check if the current row is valid for the column
        if(is_valid_row(i, col)){
            // Assign the current row of the current column to a queen
            (*board)[i][col] = 1;
            // Recursively check if the next column has a valid solution
            if(solve_rec(col + 1)){
                return true;
            }
            // If the next column does not have a valid solution, set current column to 0
            // to backtrack
            (*board)[i][col] = 0;
        }
    }
    // If the queen cannot be placed in any row in this column
    return false;
}

bool NQueens::is_valid_row(unsigned int row, unsigned int col){
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if ((*this->board)[row][i]) { return false; }

    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if ((*this->board)[i][j]) { return false; }

    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < this->board_size; i++, j--)
        if ((*this->board)[i][j]) { return false; }

    return true;
}

void NQueens::display_board(){
    for (unsigned int i = 0; i < this->board_size; i++) {
        for (unsigned int j = 0; j < this->board_size; j++){
            cout << (*this->board)[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char*argv[])
{
    unsigned int n = stoi(argv[1]);

    NQueens Q(n);

    Q.solve_rec(0);

    Q.display_board();

    return 0;
}
