#include "node.h"

// Default constructor
Node::Node(){
    this->data = 0;
    this->next = nullptr;
    this->tail = nullptr;
}

Node::Node(int data){
    this->data = data;
    this->next = nullptr;
    this->tail = nullptr;
}

Node::Node(int data, Node* next){
    this->data = data;
    this->next = next;
    this->tail = nullptr;
}

Node::Node(int data, Node* next, Node* prev){
    this->data = data;
    this->next = next;
    this->tail = prev;
}

Node::~Node(){
    if(this->next != nullptr){
        delete this->next;
    }
    if(this->tail != nullptr){
        delete this->tail;
    }
}
