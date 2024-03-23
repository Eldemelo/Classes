//TODO Finish writing insert private method
#include "bst.h"
#include <iostream>
#include <string>
using namespace std;

BSTree::BSTree(){
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
    // Base case
    if (current == nullptr){
        return new BSTNode(value);
    }
}

// Public
void BSTree::insert(int value){
    // If the tree is empty
    if (this->root == nullptr){
        this->root = new BSTNode(value);
        return;
    }
    // If tree is not empty: recursively navigate through tree
    //BSTNode* current = this->root;
}

void BSTree::remove(int value){

}

bool BSTree::search(int value){
    return false;
}

int BSTree::height(){
    return -1;
}

void BSTree::preorder(){

}

void BSTree::inorder(){

}

void BSTree::postorder(){

}