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
        // temp[index] = 
    }
    return temp;
}

// Small method to return the hash of the size of the vector
int HashTable::getHash(int value, int size){
    return value % size;
}

// Small method to return the index using double hash of the size of the vector and collision count
// h1(k) = k % table_size
// h2(k) = k^2 % TABLE_PRIME
// dbl_hash = (h1 + (#_collisions + h2)) % table_size
int HashTable::getDoubleHash(int value, int size){
    return ((getHash(value, size) + 
    (this->collisions + ((value * value) % get_table_prime()))) 
    % this->size);
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

// Helper method to handle insertion collision by using linear probe
void HashTable::linearProbe(int value, int index){
    int original = index;
    while((index + 1 <= this->size) && index + 1 != original){
        // If the index is the last, set index to -1 (to check index 0)
        if(index + 1 == this->size){
            index = -1;
            continue;
        }
        // Thix index is empty so insert here
        if(this->table[index + 1] == 0){
            this->table[index + 1] = value;
            return;
        }
        // Increment the index by 1;
        index++;
    }
}

// Public Methods
void HashTable::insert(int num){
    // If the table is 70% or more full
    if((this->amountFilled * 100) / (this->size * 100) >= 70){
        this->table = resize_table();
    }
    int index = getHash(num, this->size);

    // We have a collision
    if(this->table[index] != 0){
        // Increment the number of collisions
        this->collisions++;
        switch(this->mode){
            // Linear Probing
            case 0:
                linearProbe(num, this->size);
                break;
            // Double Hashing
            case 1:
                int index = getDoubleHash(num, this->size);
                this->table[index] = num;
                break;
            // Separate Chaining
            case 2:
                break;
        }
    }
    // There is no collision, so insert at index
    else{
        this->table[index] = num;
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