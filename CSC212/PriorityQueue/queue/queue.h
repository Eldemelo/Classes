#pragma once
#include "node.h"
#include <vector>
#include <string>

using namespace std;

// head
//  5  ->  3  ->  8  ->  6  -> X
// p1

class Queue{
    private:
        Node* head;
        Node* tail;
    public:
        ~Queue();
        Queue();
        // Overloading
        Queue(int data);
        Queue(std::vector<int> vec);
        // My functions
        void push_back(int data);
        void remove();
        string to_string();
        int peek();
};
