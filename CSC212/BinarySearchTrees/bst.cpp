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
    // Base case
    if (current == nullptr){
        return new BSTNode(value);
    }
}

// Public
void BSTree::insert(int value){
    // If the tree is empty
    // if (this->root == nullptr){
    //     this->root = new BSTNode(value);
    //     return;
    // }
    // If tree is not empty: recursively navigate through tree
    //BSTNode* current = this->root;
}

void BSTree::remove(int value){

}

bool BSTree::search(int value){
    return false;
}

int BSTree::height(BSTNode* current, int currHeight = 0){
    // base case
    cout << currHeight << endl;
    if(current->left == nullptr && current->right == nullptr){
        cout << "Bottom" << endl;
        return currHeight;
    }
    int right = 0;
    int left = 0;
    if(current->left != nullptr){
        cout << "down left" << endl;
        left = height(current->left, currHeight + 1); 
    }
    if(current->right != nullptr){
        cout << "down right" << endl;
        right = height(current->right, currHeight + 1);
    }
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