#include "linked_list.h"
#include <iostream>


LinkedList::LinkedList(){
    this->head = nullptr;
    size = 0;
}


LinkedList::LinkedList(int data){
    this->head = new Node(data);
    size = 1;
}


LinkedList::LinkedList(std::vector<int> vec){
    this->head = new Node(vec[0]);
    Node* temp = this->head;
    for(int i = 1; i < vec.size(); i++)
    {
        temp->next = new Node(vec[i]);
        temp = temp->next;
        size += 1;
    }
}

LinkedList::~LinkedList(){
    delete head;
}


void LinkedList::push_front(int data){
    Node* temp = this->head;
    this->head = new Node(data,temp);
}

void LinkedList::push_back(int data){
    Node* temp = this->head;
    while(temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = new Node(data);
}

void LinkedList::insert(int data, int idx){
    Node* temp = this->head;
    for(int i = 1; i < idx; i++)
    {
        if (temp->next != nullptr)
        {
            temp = temp->next;
        }
    }
    temp->next = new Node(data,temp->next);
    size += 1;
}

void LinkedList::remove(int data){
    Node* temp = this->head;
    while(temp->next != nullptr && temp->next->data != data)
    {
        temp = temp->next;
        std::cout << "a ";
    }
    Node* del = temp->next;
    temp->next = del->next;
    delete del;
}


bool LinkedList::contains(int data){
    Node* temp = this->head;
    while(temp != nullptr)
    {
        if(temp->data == data)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
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
