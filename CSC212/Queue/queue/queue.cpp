#include "queue.h"
#include <vector>

using namespace std;

// Default Constructor
Queue::Queue(){
    this->head = nullptr;
    this->tail = nullptr;
}

// O(1)
Queue::Queue(int data){
    this->head = new Node(data);
    this->tail = this->head;
}

// O(n)
Queue::Queue(vector<int> vec){
    if(vec.size() == 0){
        this->head = nullptr;
        this->tail = nullptr;
    }else{
        this->head = new Node(vec[0]);
        Node* temp = this->head;
        this->tail = this->head;

        for(int i = 1; i < vec.size(); i++){
            temp->next = new Node(vec[i]);
            temp = temp->next;
            this->tail = temp;
            // ->    de-reference + dot operator
            //temp = (*temp).next;
        }
    }
}

Queue::~Queue(){
    if(this->head != nullptr){
        if(this->tail != this->head){
            delete this->head;
            delete this->tail;
        }
        else{
            delete this->head;
        }
    }
}


void Queue::push_back(int data){
    if(this->head == nullptr){
        this->head = new Node(data);
        this->tail = this->head;
        // Assign tail
    }
    // handle if tail is nullptr;
    else{
        // Make a node pointer to the last node
        Node* tmp = this->tail;
        // Set last node's "next" pointer to new node
        tmp->next = new Node(data);
        // Move tail to new node
        this->tail = tmp->next;
    }
}

void Queue::remove(){
    if(this->head == nullptr){
        return;
    }
    else{
        // set pointer to first node
        Node* temp = this->head;
        // Move head to next node
        this->head = this->head->next;
        // Delete old head
        delete temp;
    }
}

int Queue::peek(){
    if (this->head != nullptr){
        return this->head->data;
    }
}

string Queue::to_string(){
    string stringified;
    Node* tmp = this->head;

    while(tmp != nullptr){
        stringified += std::to_string(tmp->data) + " ";
        tmp = tmp->next;
    }

    return stringified;
}