//TODO Finish writing insert private method
#include "bst.h"

BSTree::BSTree(){
}

BSTree::BSTree(int value){
    this->root = new BSTNode(value);
}

void BSTree::destroyRec(BSTNode* current){
    if(current != nullptr){
        destroyRec(current->left);
        destroyRec(current->right);
        delete current;
    }
}

void BSTree::destroy(){
    destroyRec(this->root);
}

// Private
BSTNode* BSTree::insert(int value, BSTNode* current){
    // Base case
    if (current == nullptr){
        current = new BSTNode(value);
    }
    else if(current->left == nullptr && ){}
}

// Public
void BSTree::insert(int value){
    // If the tree is empty
    if (this->root == nullptr){
        this->root = new BSTNode(value);
        return;
    }
    // If tree is not empty: recursively navigate through tree
    insert(value, this->root);
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