#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class arithmetic{
    private:
        vector<char> operations;
        vector<string> values;
        bool isOperator(string token);
        int getPresidence(string operation);
        bool leftAssociative(string firstOp, string secondOp);
    public:
    arithmetic();
    arithmetic(string equation);
};