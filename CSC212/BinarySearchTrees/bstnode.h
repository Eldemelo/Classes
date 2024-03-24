// Pre-planning; What am I thinking I'll need
// Private pointers to left and right nodes
// functions to update left / right nodes

class BSTNode{
    private:
        int value;
        BSTNode* left;
        BSTNode* right;
        
        friend class BSTree;
    public:
        BSTNode();
        ~BSTNode();
        BSTNode(int value);
};