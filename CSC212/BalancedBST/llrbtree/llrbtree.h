#pragma once

#include <iostream>
#include <ostream>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the RBTree class.
// I.E. RBTree is made up of RBTNode
class RBTNode
{
    private:
        int data;
        RBTNode* left;
        RBTNode* right;

    public:
        RBTNode(int data);
        ~RBTNode();

    friend class RBTree;
};

// Public versions: accept a single parameter so the usage of the class is neat.
// Private version: implement the functions recursively
class RBTree
{
    private:
        RBTNode* _root;

        RBTNode* insert(int data, RBTNode* root);
        RBTNode* remove(int data, RBTNode* root);
        RBTNode* find_ios(RBTNode* root, bool& disconnect);
        int height(RBTNode* root);

        void preorder(RBTNode* root, std::ostream& os);
        void inorder(RBTNode* root, std::ostream& os);
        void postorder(RBTNode* root, std::ostream& os);

        void destroy(RBTNode* root);
        bool search(int data, RBTNode* root);

    public:
        RBTree();
        ~RBTree();

        void insert(int data);
        void remove(int data);
        int height();

        void preorder(std::ostream& os = std::cout);
        void inorder(std::ostream& os = std::cout);
        void postorder(std::ostream& os = std::cout);

        bool search(int data);

};
