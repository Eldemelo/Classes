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

void BSTree::insert(int value){

}

void BSTree::insert(int value){

}
void BSTree::remove(int value){

}
bool BSTree::search(int value){

}
int BSTree::height(){
    
}