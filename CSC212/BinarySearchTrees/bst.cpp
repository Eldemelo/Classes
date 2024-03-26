//TODO Finish writing insert private method
#include "bst.h"
#include <iostream>
#include <string>
using namespace std;

BSTree::BSTree(){
    this->root = nullptr;
}

BSTree::BSTree(int value){
    this->root->value = value;
    this->root->left = nullptr;
    this->root->right = nullptr;
}

void BSTree::destroyRec(BSTNode* current){
    if(current == nullptr){
        return;
    }
    destroyRec(current->left);
    destroyRec(current->right);
    delete current;
}

void BSTree::destroy(){
    destroyRec(this->root);
    this->root = nullptr;
    return;
}

// Private
BSTNode* BSTree::insert(int value, BSTNode* current){
    if (value > current->value){
        if(current->right == nullptr){
            current->right = new BSTNode(value);
            return current->right;
        }
        return insert(value, current->right);
    }
    else{
        if(current->left == nullptr){
            current->left = new BSTNode(value);
            return current->left;
        }
        return insert(value, current->left);
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

BSTNode* BSTree::remove(BSTNode* current, int value){
    if(current == nullptr){
        return nullptr;
    }
    // value is smaller than current node
    else if(value < current->value){
        current->left = remove(current->left, value);
    }
    // Value is larger than current node
    else if(value > current->value){
        current->right = remove(current->right, value);
    }
    // value matches current node
    else{
        BSTNode* temp;
        // If there is no left branch
        if(current->left == nullptr){
            temp = current->right;
            delete current;
            return temp;
        }
        // If there is no right branch
        else if(current->right == nullptr){
            temp = current->left;
            delete current;
            return temp;
        }
        // Set pointer to right node
        temp = current->right;
        // Move pointer as far left as possible
        while(temp->left != nullptr){
            temp = temp->left;
        }
        // Set current node's value = to new pointer value
        current->value = temp->value;
        // Set current right's pointer to 
        current->right = remove(current->right, temp->value);
    }
    return current;
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

int BSTree::height(BSTNode* current){
    // base case
    if(current == nullptr){
        return -1;
    }
    int right = height(current->right);
    int left = height(current->left); 
    // Return the maximum of left and right
    return(left > right ? left + 1 : right + 1);
}

int BSTree::height(){
    return height(this->root);
}

// Private
void BSTree::preorder(BSTNode* current, ostream& os){
    // Base case
    if(current == nullptr){
        return;
    }
    else{
        os << to_string(current->value) + " ";
    }
    preorder(current->left, os);
    preorder(current->right, os);
    return;
}

// Public
void BSTree::preorder(ostream& os){
    preorder(this->root, os);
    os << endl;
    return;
}

void BSTree::inorder(BSTNode* current, ostream& os){
    // First check if there is a node to the left
    if(current->left != nullptr){
        inorder(current->left, os);
    }
    os << to_string(current->value) + " ";
    if(current->right != nullptr){
        inorder(current->right, os);
    }
    return;

}
void BSTree::inorder(ostream& os){
    inorder(this->root, os);
    os << endl;
    return;
}

void BSTree::postorder(BSTNode* current, ostream& os){
    // Base case
    if(current == nullptr){
        return;
    }
    postorder(current->left, os);
    postorder(current->right, os);
    os << to_string(current->value) + " ";
    return;
}

void BSTree::postorder(ostream& os){
    postorder(this->root, os);
    os << endl;
    return;
}