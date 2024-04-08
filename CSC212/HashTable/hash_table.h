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
        void resize_table();
        int get_table_prime();
        int getHash(int value, int size);
        void doubleHash(int value);
        int getDoubleHash(int value, int collisions);
        void linearProbe(int value);
        void chaining(int value);
        vector<vector<int>> resizeInsert(int value, vector<vector<int>> temp);
        vector<vector<int>> newTableInsert(int val, int size, vector<vector<int>> newTable);
    public:
        HashTable();
        HashTable(int mode);
        void insert(int num);
        void print_table();
        int get_num_collisions();
};