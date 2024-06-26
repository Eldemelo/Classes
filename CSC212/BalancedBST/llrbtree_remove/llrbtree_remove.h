#pragma once

#include <iostream>
#include <ostream>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the LLRBTree class.
// I.E. LLRBTree is made up of LLRBTNode
class LLRBTNode
{
    private:
        int data;
        LLRBTNode* left;
        LLRBTNode* right;
        bool red;

    public:
        LLRBTNode();
        LLRBTNode(int data);
        ~LLRBTNode();

    friend class LLRBTree;
};

// Public versions: accept a single parameter so the usage of the class is neat.
// Private version: implement the functions recursively
class LLRBTree
{
    private:
        LLRBTNode* _root;

        LLRBTNode* insert(int data, LLRBTNode* root);
        LLRBTNode* remove(int data, LLRBTNode* root);
        LLRBTNode* find_ios(LLRBTNode* root, bool& disconnect);
        int height(LLRBTNode* root);

        void preorder(LLRBTNode* root, std::ostream& os);
        void inorder(LLRBTNode* root, std::ostream& os);
        void postorder(LLRBTNode* root, std::ostream& os);

        void destroy(LLRBTNode* root);
        bool search(int data, LLRBTNode* root);

        LLRBTNode* rotateLeft(LLRBTNode* node);
        LLRBTNode* rotateRight(LLRBTNode* node);
        LLRBTNode* flipColors(LLRBTNode* node);
        
        LLRBTNode* moveRedLeft(LLRBTNode* node);
        LLRBTNode* moveRedRight(LLRBTNode* node);

    public:
        LLRBTree();
        ~LLRBTree();

        void insert(int data);
        void remove(int data);
        int height();

        void preorder(std::ostream& os = std::cout);
        void inorder(std::ostream& os = std::cout);
        void postorder(std::ostream& os = std::cout);

        bool search(int data);

};
