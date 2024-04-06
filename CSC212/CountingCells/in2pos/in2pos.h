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
    public:
    arithmetic();
    arithmetic(string equation);
};