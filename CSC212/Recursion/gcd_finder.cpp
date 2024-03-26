#include <iostream>
#include <string>
using namespace std;

int greatestCommonDenominator(int value1, int value2, int i = -1){
    // If i = -1, check for smaller value
    if(i == -1){
        if(value1 > value2){
            i = value2;
        }
        else{
            i = value1;
        }
    }
    // If i has reached one of the values, the lowest GCD is 1
    //cout << "Value 1: " << value1 << endl << "Value 2: " << value2 << endl << "Current iteration: " << i << endl;
    if(i <= 1){
        //cout << "No more values";
        return 1;
    }
    // Check next 5 digits unless i <= 1
    // If both values can be divided evenly by i
    else if(value1 % i == 0 && value2 % i == 0){
        return i;
    }
    else if(value1 % (i-1) == 0 && value2 % (i-1) == 0){
        return i-1;
    }
    return greatestCommonDenominator(value1, value2, i - 2);
}

int main(int argc, char* argv[]){
    // Save CLA integer
    int value1 = stoi(argv[1]);
    int value2 = stoi(argv[2]);
    int gcd = greatestCommonDenominator(value1, value2);
    cout << gcd << endl;
}