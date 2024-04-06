#include "hash_table.h"


HashTable::HashTable(){
    
}

HashTable::HashTable(int mode){
    this->mode = mode;
    this->amountFilled = 0;
    this->collisions = 0;
    // Initialize vector with size 1 and default value 0
    this->table = vector(1, 0);
    this->size = 1;
}

// Private Methods
vector<int> HashTable::resize_table(){
    this->size *= 2;
    vector<int> temp(this->size, 0);
    for(int value : this->table){
        int index = getHash(value, this->size);
        temp[index] = 
    }
    return temp;
}

// Small method to return the hash of the size of the vector
int HashTable::getHash(int value, int size){
    return value % size;
}

// Returns the highest prime number less than the size
int HashTable::get_table_prime(){
    int prime = 0;
    for(int i = this->size; i > 0; i--){
        bool isPrime = true;
        for(int j = 2; j < i; j++){
            if(i % j == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime){
            prime = i;
            break;
        }
    }
    return prime;
}

// Public Methods
void HashTable::insert(int num){
    // If the table is 70% or more full
    if((this->amountFilled * 100) / (this->size * 100) >= 70){
        this->table = resize_table();
    }
    
}

void HashTable::print_table(){
    for(int i = 0; i < this->size; i++){
        cout << i << ": " << this->table[i] << endl;
    }
}

int HashTable::get_num_collisions(){
    return this->collisions;
}