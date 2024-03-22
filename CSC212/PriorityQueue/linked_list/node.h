#pragma once


// head
//  5  ->  3  ->  8  ->  6  -> X
// p1


class Node{
    private:
        int data;
        Node* next;
        Node* tail;

        friend class LinkedList;
        friend class Queue;
        friend class Priority_Queue;
    public:
        Node();
        // Overloading
        Node(int data);
        Node(int data, Node* next);
        Node(int data, Node* next, Node* prev);
        ~Node();
};

