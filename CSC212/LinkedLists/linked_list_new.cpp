#include "linked_list.h"
#include <iostream>


LinkedList::LinkedList(){
    // Create head with nullptr and size
    this->head = nullptr;
    size = 0;
}


LinkedList::LinkedList(int data){
    // Create node with first value
    this->head = new Node(data);
    size = 1;
}


LinkedList::LinkedList(std::vector<int> vec){
    this->head = new Node;

}

LinkedList::~LinkedList(){

}


void LinkedList::push_front(int data){

}

void LinkedList::push_back(int data){

}

void LinkedList::insert(int data, int idx){

}

void LinkedList::remove(int data){

}


bool LinkedList::contains(int data){

}


int LinkedList::get_size(){
    return this->size;
}

// O(n)
std::string LinkedList::to_string(){
    std::string stringified;
    Node* tmp = this->head;

    while(tmp != nullptr){
        stringified += std::to_string(tmp->data) + " ";
        tmp = tmp->next;
    }

    return stringified;
}
