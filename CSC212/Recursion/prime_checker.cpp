#include <iostream>
#include <string>
using namespace std;

// Recursive function to check if a number is prime by saving current iterative number and original
bool isPrime(int n, int i = 2){
    // If the number is 0 or 1 is is not prime
    if(n <= 1){
        return false;
    }
    // If the number is 2, it is prime
    else if(n == 2){
        return true;
    }
    // If the number is divisible by any number not itself and 1
    else if(n % i == 0){
        return false;
    }
    // If the iteration squared is more than the number
    else if(i * i > n){
        return true;
    }
    return isPrime(n, i + 1);
}

int main(int argc, char* argv[]){
    // Save CLA integer
    int value = stoi(argv[1]);
    bool primeNumber = isPrime(value);
    cout << primeNumber << endl;
}