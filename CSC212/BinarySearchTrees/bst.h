#include "bstnode.h"

// What am I expecting to need?
// public functions to call from main: insert, search, remove(destroy)

class BSTree{
    private:
        BSTNode* root;
    public:
        BSTree();
        ~BSTree();
        void insert(int value);

};