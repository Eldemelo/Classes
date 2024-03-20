#include "bst.h"
#include <fstream>
#include <sstream>
#include <bitset>

using namespace std;

// void print_tree(BSTree* tree, int mode);
void print_tree(BSTree* tree, bitset<3> mode);

// <file_name> <traversal_method>
int main(int argc, char*argv[]){
    ifstream ifs(argv[1]);
    // int mode = stoi(argv[2]);
    bitset<3> mode(*argv[2]);

    BSTree* tree = new BSTree();

    string line;

    // Get the numbers to be inserted
    getline(ifs, line);
    stringstream ss(line);

    int num;
    // Insert the numbers
    while(ss >> num){
        tree->insert(num);
        print_tree(tree, mode);
        cout << "Height: " << tree->height() << endl;
    }

    // Get the numbers to be searched
    getline(ifs, line);
    ss.clear();
    ss.str(line);

    // Search for the numbers
    while(ss >> num){
         cout << tree->search(num) << endl;
    }

    // Get the numbers to be removed
    getline(ifs, line);
    ss.clear();
    ss.str(line);

    // Remove the numbers
    while(ss >> num){
        tree->remove(num);
        print_tree(tree, mode);
        cout << "Height: " << tree->height() << endl;
    }

    // Destroy the tree
    tree->destroy();
    cout << "Height: " << tree->height() << endl;
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
// Old, boring way of interpreting the bitstring
// void print_tree(BSTree* tree, int mode){
//     if(mode == 1 || mode == 3 || mode == 5 || mode == 7){
//         tree->preorder();
//     }
//     if(mode == 2 || mode == 3 || mode == 6 || mode == 7){
//         tree->inorder();
//     }
//     if(mode == 4 || mode == 5 || mode == 6 || mode == 7){
//         tree->postorder();
//     }
// }

// New, exciting way of interpreting the bitstring!
void print_tree(BSTree* tree, bitset<3> mode){
    if(mode[0]){
        tree->preorder();
    }
    if(mode[1]){
        tree->inorder();
    }
    if(mode[2]){
        tree->postorder();
    }
}