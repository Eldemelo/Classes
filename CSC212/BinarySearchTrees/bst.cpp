//TODO Finish writing insert private method
#include "bst.h"
#include <iostream>
#include <string>
using namespace std;

BSTree::BSTree(){
    this->root = nullptr;
    cout << 'hi';
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

void BSTree::remove(int value){

}

bool BSTree::search(int value){
    return false;
}

int BSTree::height(BSTNode* current, int currHeight = 0){
    // base case
    if(current == nullptr){
        return currHeight;
    }
    int left = height(current->left, currHeight + 1);
    int right = height(current->right, currHeight + 1);

    if(left > right){
        return left;
    }
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