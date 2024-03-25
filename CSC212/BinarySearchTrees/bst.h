#include "bstnode.h"
#include <ostream>
#include <string>
#include <iostream>

// What am I expecting to need?
// public functions to call from main: insert, search, remove(destroy)
using namespace std;

class BSTree{
    private:
        BSTNode* root;
        void destroyRec(BSTNode* current);
        BSTNode* insert(int value, BSTNode* current);
        int height(BSTNode* current, int height);
        bool search(BSTNode* current, int value);
        BSTNode* remove(BSTNode* current, int value);
        void preorder(BSTNode* current, ostream&);
        void inorder(BSTNode* current, ostream&);
        void postorder(BSTNode* current, ostream&);
    public:
        BSTree();
        BSTree(int value);
        void destroy(); // Function to iteratively delete all nodes and then delete root

        void insert(int value);
        void remove(int value);
        bool search(int value);
        int height();
        void preorder(ostream& os = cout);
        void inorder(ostream& os = cout);
        void postorder(ostream& os = cout);
};