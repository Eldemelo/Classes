#include "linked_list.h"
#include <iostream>
using namespace std;

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
    this->head = nullptr;
    delete this->head;
}


void LinkedList::push_front(int data){
    // Save head
    Node *temp = this->head;
    // Update head with new node pointing to old head
    this->head = new Node(data, temp);
    size += 1;
}

void LinkedList::push_back(int data){
    // If first value is to be removed
    if(this->head == nullptr){
        this->push_front(data);
        return;
    }
    // Save head
    Node *temp = this->head;
    // As long as we are not in the node
    while(temp->next != nullptr){
        // Navigate to next node
        temp = temp->next;
    }
    // Assign old last node's "next" a pointer to the new node
    temp->next = new Node(data);
    size += 1;
}

void LinkedList::insert(int data, int idx){
    // Save head;
    Node *temp = this->head;
    // If the head is to be inserted
    if(idx == 0){
        this->push_front(data);
    }
    else{
            // Navigate to index ensuring we are within scope
        int count = 0;
        while(count < idx - 1 && temp->next != nullptr){
            count += 1;
            temp = temp->next;
        }
        // Assign current node's "next" to new node
        temp->next = new Node(data, temp->next);
        size += 1;
    }
}

void LinkedList::remove(int data){
    // Check if list is empty
    if(this->head == nullptr){
        return;
    }
    // Check first value
    if(this->head->data == data){
        // If there is no more nodes after:
        this->head = this->head->next;
        return;
    }
    else{
        //cout << "Remove: " << data << endl << endl;
        // Check the next value
        Node *temp = this->head;
        Node *prev = temp;
        // Make sure next value isn't nullptr;
        temp = temp->next;
        while(temp != nullptr){
            //cout << "NextNodeData: " << temp->next->data << endl;
            // Check next value's data
            if(temp->data == data){
                // Save current node for deletion
                Node *toDelete = temp;
                // Set current cell's pointer to skip next
                //cout << "curr: " << temp << " next: " << temp->next << " 2nd: " << temp->next->next << endl; 
                prev->next = temp->next;
                temp->next = nullptr;
                // Delete next node
                delete toDelete;
                // return
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
}


bool LinkedList::contains(int data){
    Node *temp = this->head;
    // Navigate whole list
    while(temp != nullptr){
        if(temp->data == data){
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
    string stringified;
    Node* tmp = this->head;

    while(tmp != nullptr){
        stringified += std::to_string(tmp->data) + " ";
        tmp = tmp->next;
    }

    return stringified;
}
