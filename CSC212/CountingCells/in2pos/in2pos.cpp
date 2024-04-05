#include "in2pos.h"

arithmetic::arithmetic(){

}
arithmetic::arithmetic(string equation){
    vector<string> values;
    vector<char> operations;
    istringstream ss(equation);
    string temp;
    while(ss >> temp){
        if(temp == "/" || temp == "")
    }
}


int main(int argc, char* argv[]){
    string equation = argv[1];

    arithmetic myEquation(equation);
}
