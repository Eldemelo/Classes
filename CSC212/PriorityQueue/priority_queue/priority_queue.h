#pragma once
#include "priority_node.h"
#include <vector>
#include <string>

using namespace std;

// head
//  5  ->  3  ->  8  ->  6  -> X
// p1

class Priority_Queue{
    private:
        Priority_Node* head;
    public:
        Priority_Queue();
        // Overloading
        Priority_Queue(int data, int priority);
        Priority_Queue(vector<int> vec, vector<int> priority);
        // My functions
        void push_back(int data, int priority);
        void remove();
        string to_string();
        string peek();
};
