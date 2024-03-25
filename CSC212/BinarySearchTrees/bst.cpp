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

BSTNode* BSTree::remove(BSTNode* current, int value){
    // Base case - Value not found
    if(current == nullptr){
        // Return the nullptr
        return current;
    }
    // If the value is larger than the current node
    if(value > current->value){
        // Move to the right node
        current->right = remove(current->right, value);
        return current;
    }
    else if(value < current->value){
        // Move to the left node
        current->left = remove(current->left, value);
        return current;
    }
    // If there is no left child
    if(current->left == nullptr){
        BSTNode* temp = current->right;
        delete current;
        return temp;
    }
    // If there is no right child
    else if(current->right == nullptr){
        BSTNode* temp = current->left;
        delete current;
        return temp;
    }
    // If we have two children
    else{
        // Create a pointer to the branch and its leaf
        BSTNode* branch = this->root;
        BSTNode* leaf = this->root->right;
        // Find smallest (child) node to the right
        while(leaf->left != nullptr){
            branch = leaf;
            leaf = leaf->left;
        }
        // If the node is not the root node
        if(branch != root){
            branch->left = leaf->right;
        }
        // Always assign leaf's "right branch" to the parent branch's left leaf
        else{
            branch->right = leaf->right;
        }
        this->root->value = leaf->value;
        delete leaf;
        return root;
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

// Private
void BSTree::preorder(BSTNode* current, ostream& os){
    // Base case
    if(current == nullptr){
        return;
    }
    else{
        os << current->value;
    }
    preorder(current->left, os);
    preorder(current->right, os);
    return;
}

// Public
void BSTree::preorder(ostream& os){
    preorder(this->root, os);
}

void BSTree::inorder(BSTNode* current, ostream& os){
    // First check if there is a node to the left
    if(current->left != nullptr){
        inorder(current->left, os);
    }
    os << current->value;
    if(current->right != nullptr){
        inorder(current->right, os);
    }
    return;

}
void BSTree::inorder(ostream& os){
    inorder(this->root, os);
}

void BSTree::postorder(BSTNode* current, ostream& os){
    // Base case
    if(current == nullptr){
        return;
    }
    postorder(current->left, os);
    postorder(current->right, os);
    os << current->value;
    return;
}

void BSTree::postorder(ostream& os){
    postorder(this->root, os);
}