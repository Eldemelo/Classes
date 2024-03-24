#include "bstnode.h"

BSTNode::BSTNode(){
    this->left = nullptr;
    this->right = nullptr;   
}

BSTNode::BSTNode(int value){
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}

BSTNode::~BSTNode(){
    // Keep empty!
}