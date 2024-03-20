#include "priority_queue.h"
#include <vector>

using namespace std;

// Default Constructor
Priority_Queue::Priority_Queue(){
    this->head = nullptr;
}

// O(1)
Priority_Queue::Priority_Queue(int data, int priority){
    this->head = new Priority_Node(data, priority);
}

// O(n)
Priority_Queue::Priority_Queue(vector<int> vec, vector<int> priority){
    if(vec.size() == 0){
        this->head = nullptr;
    }else{
        this->head = new Priority_Node(vec[0], priority[0]);
        Priority_Node* temp = this->head;

        for(int i = 1; i < vec.size(); i++){
            temp->next = new Priority_Node(vec[i], priority[i]);
            temp = temp->next;
            // ->    de-reference + dot operator
            //temp = (*temp).next;
        }
    }
}

Priority_Queue::~Priority_Queue(){
    if(this->head != nullptr){
        delete this->head;
    }
}

void Priority_Queue::push_back(int data, int priority){
    if(this->head == nullptr){
        this->head = new Priority_Node(data, priority);
    }
    // If there is only 1 value in the list
    else if(this->head->next == nullptr){
        // Check if the first value has higher or lower priority
        if(this->head->priority < priority){
            // append the next value
            Priority_Node* temp = this->head;
            temp->next = new Priority_Node(data, priority);
        }
        else{
            // save current node's memory location
            Priority_Node* temp = this->head;
            // Set head to a new node
            this->head = new Priority_Node(data, priority);
            // Set new head's pointer to old head
            this->head->next = temp;
        }
    }
    else{
        // Make a node pointer to the first node
        Priority_Node* temp = this->head;
        // Navigate through the list until the next node's priority is lower
        while(temp->next->priority <= priority){
            temp = temp->next;
        }
        // save current node's next
        Priority_Node* saved = temp->next;
        // Set current node's pointer to a new node with the new data
        temp->next = new Priority_Node(data, priority);
        // navigate to the new node
        temp = temp->next;
        // Update new node's next to saved node
        temp->next = saved;
    }
}

void Priority_Queue::remove(){
    if(this->head == nullptr){
        return;
    }
    else{
        // set pointer to first node
        Priority_Node* temp = this->head;
        // Move head to next node
        this->head = temp->next;
        // Delete old head
        delete temp;
    }
}

string Priority_Queue::peek(){
    return "(" + std::to_string(this->head->data) + "," + std::to_string(this->head->priority) + ")";
}

string Priority_Queue::to_string(){
    string stringified;
    Priority_Node* tmp = this->head;

    while(tmp != nullptr){
        stringified += "(" + std::to_string(tmp->data) + "," + std::to_string(tmp->priority) + ") ";
        tmp = tmp->next;
    }

    return stringified;
}