#include "bstnode.h"

// What am I expecting to need?
// public functions to call from main: insert, search, remove(destroy)

class BSTree{
    private:
        BSTNode* root;
        void destroyRec(BSTNode* current);
        BSTNode* insert(int value, BSTNode* current);
    public:
        BSTree();
        BSTree(int value);
        void destroy(); // Function to iteratively delete all nodes and then delete root

        void insert(int value);
        void remove(int value);
        bool search(int value);
        int height();
        void preorder();
        void inorder();
        void postorder();
};