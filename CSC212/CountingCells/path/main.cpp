#include "path.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    string fName = argv[1];
    int rows = stoi(argv[2]);
    int cols = stoi(argv[3]);

    grid cellGrid(fName, rows, cols);
    
}