#include "llrbtree.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
 * Node Class Functions
*/

LLRBTNode::LLRBTNode(){
    this->data = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->red = true;
}

LLRBTNode::LLRBTNode(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->red = true;
}

LLRBTNode::~LLRBTNode(){

}

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

// Private method to rotate tree left
LLRBTNode* LLRBTree::rotateLeft(LLRBTNode* node){
    LLRBTNode* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->red = node->red;
    node->red = true;
    return temp;
}

// Private method to rotate tree right
LLRBTNode* LLRBTree::rotateRight(LLRBTNode* node){
    LLRBTNode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->red = node->red;
    node->red = true;
    return temp;
}

// Method to flip node and its 2 children
LLRBTNode* LLRBTree::flipColors(LLRBTNode* node){
    // Flip current node
    node->red == true ? node->red = false : node->red = true;
    // If node to left exists, flip
    if(node->left){
        node->left->red ? node->left->red = false : node->left->red = true;
    }
    // If node to right exists, flip
    if(node->right){
        node->right->red ? node->right->red = false : node->right->red = true;
    }
    return node;
}

LLRBTNode* LLRBTree::insert(int data, LLRBTNode* node){
    if(!node){
        return new LLRBTNode(data);
    }
    // Go left if data < data at this Node
    if(data < node->data){
        node->left = insert(data, node->left);
    // Go right otherwise
    }else{
        node->right = insert(data, node->right);
    }
    // Ensure red/black rules are followed
    bool valid = false;
    while(!valid){
        valid = true;
        // If both children are red
        if((node->left && node->left->red) && (node->right && node->right->red)){
            valid = false;
            node = flipColors(node);
        }
        // If the left node is black and the right node is red
        if(((node->left && !node->left->red) || !node->left) && (node->right && node->right->red)){
            valid = false;
            node = rotateLeft(node);
        }
        // If the node to the left and the grandchild to the left is red
        if((node->left && node->left->red) && (node->left->left && node->left->left->red)){
            valid = false;
            node = rotateRight(node);
        }
    }
    return node;
}

LLRBTNode* LLRBTree::remove(int data, LLRBTNode* node){
    if(!node){
        return nullptr;
    }

    // We found what we're looking for, delete it.
    if(data == node->data){
        LLRBTNode* temp;
        // This is a leaf node
        if(node->left == node->right){
            delete node;
            return nullptr;
        }

        // This node nodeas 1 child
        if(!node->left != !node->right){
            // Set temp to whichever child exists
            node->left ? temp = node->left : temp = node->right;

            delete node;
            return temp;
        }

        // This node nodeas 2 children
        // Find the in-order successor
        temp = node->right;

        while(temp->left){
            temp = temp->left;
        }

        // Copy the data to this node and delete the original
        node->data = temp->data;
        node->right = remove(temp->data, node->right);
        return node;
    }

    // This is not the Node we're looking for, recursively find the data we want to delete
    if(data < node->data){
        node->left = remove(data, node->left);
    }else{
        node->right = remove(data, node->right);
    }

    return node;
}

LLRBTNode* LLRBTree::find_ios(LLRBTNode* node, bool& disconnect){
    if(!node->left){
        disconnect = true;
        return node;
    }
    LLRBTNode* temp = find_ios(node->left, disconnect);

    if(disconnect){
        node->left = nullptr;
        disconnect = false;
    }

    return temp;
}

int LLRBTree::height(LLRBTNode* node){
    if(!node){
        return -1;
    }
    int left = height(node->left);
    int right = height(node->right);

    return (left > right ? left + 1 : right + 1);
}

void LLRBTree::preorder(LLRBTNode* node, ostream& os){
    if(!node){
        return;
    }

    os << node->data << ":" << node->red << " ";
    this->preorder(node->left, os);
    this->preorder(node->right, os);

    return;
}

void LLRBTree::inorder(LLRBTNode* node, ostream& os){
    if(!node){
        return;
    }

    this->inorder(node->left, os);
    os << node->data << ":" << node->red << " ";
    this->inorder(node->right, os);

    return;
}

void LLRBTree::postorder(LLRBTNode* node, ostream& os){
    if(!node){
        return;
    }

    this->postorder(node->left, os);
    this->postorder(node->right, os);
    os << node->data << ":" << node->red << " ";

    return;
}

void LLRBTree::destroy(LLRBTNode* node){
    if(!node){
        return;
    }

    this->destroy(node->left);
    this->destroy(node->right);
    delete node->left;
    delete node->right;
}

bool LLRBTree::search(int data, LLRBTNode* node){
    if(!node){
        return false;
    }

    if(data == node->data){
        return true;
    }

    if(data < node->data){
        return this->search(data, node->left);
    }else{
        return this->search(data, node->right);
    }
}

/*
 * Public Functions
*/

LLRBTree::LLRBTree(){
    this->_root = nullptr;
}

LLRBTree::~LLRBTree(){
    delete this->_root;
}

void LLRBTree::insert(int data){
    if(!this->_root){
        this->_root = this->insert(data, this->_root);
        this->_root->red = false;
        return;
    }
    this->_root = this->insert(data, this->_root);
    this->_root->red = false;
}

void LLRBTree::remove(int data){
    this->_root = this->remove(data, this->_root);
}

int LLRBTree::height(){
    return this->height(this->_root);
}

void LLRBTree::preorder(ostream& os){
    this->preorder(this->_root, os);
    os << "\n";
}

void LLRBTree::inorder(ostream& os){
    this->inorder(this->_root, os);
    os << "\n";
}

void LLRBTree::postorder(ostream& os){
    this->postorder(this->_root, os);
    os << "\n";
}

bool LLRBTree::search(int data){
    return this->search(data, this->_root);
}