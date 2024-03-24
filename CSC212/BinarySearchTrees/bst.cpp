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
    if(current->left == nullptr && current->right == nullptr){
        delete current;
    }
    // If there is a left node, move to that node
    else if(current->left != nullptr){
        destroyRec(current->left);
    }
    // If there is a right node, move to that node
    else if(current->right != nullptr){
        destroyRec(current->right);
    }
    return;
}

void BSTree::destroy(){
    destroyRec(this->root);
}

// Private
BSTNode* BSTree::insert(int value, BSTNode* current){
    // Base case; has no more branches to navigate
    if (current->left == nullptr && current->right == nullptr){
        // If the value to insert is larger
        if (value > current->value){
            current->right = new BSTNode(value);
        }
        else{
            current->left = new BSTNode(value);
        }
    }
    // If the value is smaller than current
    if(value < current->value){
        // If there is no left branch
        if(current->left == nullptr){
            current->left = new BSTNode(value);
        }
        // If the left branch exists, navigate to it
        else{
            return insert(value, current->left);
        }
    }
    // If the value is larger than current
    else if(value > current->value){
        // If there is no right branch
        if(current->right == nullptr){
            current->right = new BSTNode(value);
        }
        // Navigate to branch
        else{
            return insert(value, current->right);
        }
    }
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

void BSTree::remove(int value){

}

bool BSTree::search(int value){
    return false;
}

int BSTree::height(BSTNode* current, int currHeight = 0){
    // base case
    if(current->left == nullptr && current->right == nullptr){
        return currHeight;
    }
    int right = 0;
    int left = 0;
    // If there is a left branch
    if(current->left != nullptr){
        left = height(current->left, currHeight + 1); 
    }
    // If there is a right branch
    if(current->right != nullptr){
        right = height(current->right, currHeight + 1);
    }
    // If the left branch has a higher height, return left
    if(left > right){
        return left;
    }
    // Return right
    return right;
}

int BSTree::height(){
    // If there is no root ; There is no layers
    if(this->root == nullptr){
        return -1;
    }
    else{
        return height(this->root);
    }
}

void BSTree::preorder(){

}

void BSTree::inorder(){

}

void BSTree::postorder(){

}