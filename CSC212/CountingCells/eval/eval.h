#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

class arithmetic{
    private:
        vector<char> operations;
        vector<string> values;
        bool isOperator(string token);
        int performCalc(string operation, string firstVal, string secondVal);
    public:
    arithmetic();
    arithmetic(string equation);
};