#include "Priority_Node.h"

// Default constructor
Priority_Node::Priority_Node(){
    this->data = 0;
    this->priority = 0;
    this->next = nullptr;
}

Priority_Node::Priority_Node(int data, int priority){
    this->data = data;
    this->priority = priority;
    this->next = nullptr;
}

Priority_Node::Priority_Node(int data, int priority, Priority_Node* next){
    this->data = data;
    this->priority = priority;
    this->next = next;
}

Priority_Node::~Priority_Node(){
    if(this->next != nullptr){
        delete this->next;
    }
}
