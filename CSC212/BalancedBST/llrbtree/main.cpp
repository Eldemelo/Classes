#include "llrbtree.h"
#include <fstream>
#include <sstream>
#include <bitset>

using namespace std;

void print_tree(LLRBTree* tree, bitset<3> mode, ofstream& os);

int main(int argc, char*argv[]){
    ifstream ifs(argv[1]);
    bitset<3> mode(*argv[2]);
    ofstream ofs(argv[3]);

    LLRBTree tree;

    string line;

    // Get the numbers to be inserted
    getline(ifs, line);
    stringstream ss(line);

    int num;
    // Insert the numbers
    while(ss >> num){
        tree.insert(num);
        print_tree(&tree, mode, ofs);
        cout << "Height: " << tree.height() << endl;
    }
    ofs << "Tree Height: " << tree.height();
    ifs.close();
    ofs.close();
}

/*
 * pre = 1
 * in = 2
 * post = 4
 * pre+in = 3
 * pre+post = 5
 * in+post = 6
 * pre+in+post = 7
 */
void print_tree(LLRBTree* tree, bitset<3> mode, ofstream& os){
    if(mode[0]){
        tree->preorder(os);
    }
    if(mode[1]){
        tree->inorder(os);
    }
    if(mode[2]){
        tree->postorder(os);
    }
}
