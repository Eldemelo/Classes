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
    this->red = false;
}

LLRBTNode::LLRBTNode(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->red = false;
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
    LLRBTNode* p = node->right;
    node->right = p->left;
    p->left = node;
    return p;
}

// Private method to rotate tree right
LLRBTNode* LLRBTree::rotateRight(LLRBTNode* node){
    LLRBTNode* p = node->left;
    node->left = p->right;
    p->right = node;
    return p;
}

// Method to navigate through the tree and flip each node's color
void LLRBTree::flipColors(LLRBTNode* node){
    // Base case
    if(node == nullptr){
        return;
    }
    this->flipColors(node->left);
    this->flipColors(node->right);
    (node->red == true) ? node->red = false : node->red = true;
    return;
}

LLRBTNode* LLRBTree::insert(int data, LLRBTNode* root){
    if(!root){
        return new LLRBTNode(data);
    }

    // Determine if the tree needs to be rotated
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if(leftHeight >= rightHeight + 2){
        root = rotateRight(root);
    }
    else if(rightHeight >= leftHeight + 2){
        root = rotateLeft(root);
    }
    // Go left if data < data at this Node
    if(data < root->data){
        root->left = insert(data, root->left);
    // Go right otherwise
    }else{
        root->right = insert(data, root->right);
    }
    return root;
}

LLRBTNode* LLRBTree::remove(int data, LLRBTNode* root){
    if(!root){
        return nullptr;
    }

    // We found what we're looking for, delete it.
    if(data == root->data){
        LLRBTNode* temp;
        // This is a leaf node
        if(root->left == root->right){
            delete root;
            return nullptr;
        }

        // This node has 1 child
        if(!root->left != !root->right){
            // Set temp to whichever child exists
            root->left ? temp = root->left : temp = root->right;

            delete root;
            return temp;
        }

        // This node has 2 children
        // Find the in-order successor
        temp = root->right;

        while(temp->left){
            temp = temp->left;
        }

        // Copy the data to this node and delete the original
        root->data = temp->data;
        root->right = remove(temp->data, root->right);
        return root;
    }

    // This is not the Node we're looking for, recursively find the data we want to delete
    if(data < root->data){
        root->left = remove(data, root->left);
    }else{
        root->right = remove(data, root->right);
    }

    return root;
}

LLRBTNode* LLRBTree::find_ios(LLRBTNode* root, bool& disconnect){
    if(!root->left){
        disconnect = true;
        return root;
    }
    LLRBTNode* temp = find_ios(root->left, disconnect);

    if(disconnect){
        root->left = nullptr;
        disconnect = false;
    }

    return temp;
}

int LLRBTree::height(LLRBTNode* root){
    if(!root){
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}

void LLRBTree::preorder(LLRBTNode* root, ostream& os){
    if(!root){
        return;
    }

    os << root->data << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

void LLRBTree::inorder(LLRBTNode* root, ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data << ":" << root->red << " ";
    this->inorder(root->right, os);

    return;
}

void LLRBTree::postorder(LLRBTNode* root, ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data << ":" << root->red << " ";

    return;
}

void LLRBTree::destroy(LLRBTNode* root){
    if(!root){
        return;
    }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

bool LLRBTree::search(int data, LLRBTNode* root){
    if(!root){
        return false;
    }

    if(data == root->data){
        return true;
    }

    if(data < root->data){
        return this->search(data, root->left);
    }else{
        return this->search(data, root->right);
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
    this->_root = this->insert(data, this->_root);
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