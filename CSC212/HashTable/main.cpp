#include "hash_table.h"

using namespace std;

int main(int argc, char*argv[]){
    ifstream ifs(argv[1]);
    int mode = stoi(argv[2]);

    HashTable table(mode);

    string line;

    // Get the numbers to be inserted
    getline(ifs, line);
    stringstream ss(line);

    int num;
    // Insert the numbers
    while(ss >> num){
        table.insert(num);
    }
    table.print_table();
    cout << "Total Collisions: " << table.get_num_collisions() << endl;
}