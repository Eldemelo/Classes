#include <iostream>
#include <string>
using namespace std;

int sumOfDigits(int n){
    int total = 0;
    if (n == 0) {
        // If there are no more digits
        return 0;
    }
    else{
        // Get last digit in number and recursively call function with last removed
        return (n % 10) + sumOfDigits(n / 10);
    }
}

int main(int argc, char* argv[]){
    // Save CLA integer
    int value = stoi(argv[1]);
    int total = sumOfDigits(value);
    cout << total << endl;
}