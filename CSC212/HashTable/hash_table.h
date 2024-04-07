#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class HashTable{
    private:
        int mode;
        int size;
        int amountFilled;
        int collisions;
        vector<vector<int>> table;
        vector<int> resize_table();
        int get_table_prime();
        int getHash(int value, int size);
        int getDoubleHash(int value, int size);
        void linearProbe(int value, int index);
    public:
        HashTable();
        HashTable(int mode);
        void insert(int num);
        void print_table();
        int get_num_collisions();
};