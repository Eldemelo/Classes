//TODO Finish writing insert private method
#include "bst.h"
#include <iostream>
#include <string>
using namespace std;

BSTree::BSTree(){
    this->root = nullptr;
}

BSTree::BSTree(int value){
    this->root = new BSTNode(value);
}

void BSTree::destroyRec(BSTNode* current){
    // Base case if currently on last node of branch
    if(current != nullptr){
        if(current->left != nullptr){
            destroyRec(current->left);
            current->left = nullptr;
        }
        if(current->right != nullptr){
            destroyRec(current->right);
            current->right = nullptr;
        }
        delete current;
    }
}

void BSTree::destroy(){
    destroyRec(this->root);
}

// Private
BSTNode* BSTree::insert(int value, BSTNode* current){
    // Base case; has no more branches to navigate
    if (current == nullptr){
        return new BSTNode(value);
    }
    // If the value is smaller than current
    else if(value < current->value){
        current->left = insert(value, current->left);
    }
    // If the value is larger than current
    else if(value > current->value){
        current->right = insert(value, current->right);
    }
    // If the value is equal to current, we do nothing
    return current;
}

// Public
void BSTree::insert(int value){
    // If the tree is empty
    if (this->root == nullptr){
        this->root = new BSTNode(value);
        return;
    }
    else{
        insert(value, this->root);
    }
    return;
}

void BSTree::remove(BSTNode* current, int value){
    // Base case
    if(current == nullptr){
        return;
    }
    // If the current node matches the value to be removed
    if(current->value == value){
        // If there are no branches
        if(current->left == nullptr && current->right == nullptr && current->value == value){
            delete current;
        }
        // If there is a right node
        else if(current->right != nullptr){
            // Find the smallest number on the right side
            BSTNode* temp = current->right;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            // Set the current node's value to the smallest value on the right
            current->value = temp->value;
            delete temp;
        }
        // If there is no right node
        else{
            BSTNode* toDelete = current;
            BSTNode* temp = current->left;
            delete toDelete;
            current = temp;
        }
    }
}

void BSTree::remove(int value){
    remove(this->root, value);
}

// Private
bool BSTree::search(BSTNode* current, int value){
    bool left, right;
    // Base case ; If the current node does not exist
    if(current == nullptr){
        return false;
    }
    else if(current->value == value){
        return true;
    }
    left = search(current->left, value);
    right = search(current->right, value);
    if(left == true || right == true){
        return true;
    }
    return false;
}

// Public
bool BSTree::search(int value){
    if(this->root == nullptr){
        return false;
    }
    return search(this->root, value);
}

int BSTree::height(BSTNode* current, int currHeight = -1){
    // base case
    if(current == nullptr){
        return currHeight;
    }
    int right = height(current->right, currHeight + 1);
    int left = height(current->left, currHeight + 1); 
    // Return the maximum of left and right
    if(left > right){
        return left;
    }
    return right;
}

int BSTree::height(){
    return height(this->root);
}

void BSTree::preorder(){

}

void BSTree::inorder(){

}

void BSTree::postorder(){

}