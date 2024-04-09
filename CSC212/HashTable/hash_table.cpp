#include "hash_table.h"


HashTable::HashTable(){
    
}

HashTable::HashTable(int mode){
    this->mode = mode;
    this->amountFilled = 0;
    this->collisions = 0;
    // Initialize vector with size 1 and default value 0
    this->table = vector<vector<int>>(1, vector<int>(1, 0));
    this->size = 1;
}

// Private Methods
void HashTable::resize_table(){
    this->size *= 2;
    vector<vector<int>> temp = this->table;
    this->table = vector<vector<int>>(this->size, vector<int>(1,0));
    this->amountFilled = 0;
    for(vector<int> row : temp){
        for(int val : row){
            if(val != 0){
                insert(val);
            }
        }
    }
}

// Small method to return the hash of the size of the vector
int HashTable::getHash(int value, int size){
    return value % size;
}

// Small method to return the index using double hash of the size of the vector and collision count
// h1(k) = k % table_size
// h2(k) = k^2 % TABLE_PRIME
// dbl_hash = (h1 + (#_collisions + h2)) % table_size
void HashTable::doubleHash(int value){
    if((this->amountFilled * 1.0) / this->table.size() >= 0.7){
        resize_table();
    }

    // find original index to work with
    int localCollisions = 0;
    int index = getDoubleHash(value, localCollisions);

    // Collision
    if(this->table[index][0] != 0){
        while(this->table[index][0] != 0){
            this->collisions++;
            localCollisions++;
            index = getDoubleHash(value, localCollisions);
        }
    }
    this->table[index][0] = value;
}

// Method to find the index that is available using double hashing
int HashTable::getDoubleHash(int value, int localCollisions){
    int h1 = getHash(value, this->table.size());
    int h2 = (value * value) % get_table_prime();
    int index = (h1 + (localCollisions + h2)) % this->table.size();
    return index;
}


// Returns the highest prime number less than the size
int HashTable::get_table_prime(){
    int prime = -1;
    for(int i = this->table.size() - 1; i > 0; i--){
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
void HashTable::linearProbe(int value){
    if((this->amountFilled * 1.0) / this->table.size() >= 0.7){
        resize_table();
    }

    int index = getHash(value, this->table.size());
    while(this->table[index][0] != 0){
        this->collisions++;
        index = (index + 1) % this->table.size();
    }
    this->table[index][0] = value;
}

void HashTable::chaining(int value){
    if((this->amountFilled * 1.0) / this->table.size() >= 0.7){
        resize_table();
    }
    
    int index = getHash(value, this->table.size());
    if(this->table[index][0] != 0){
        this->collisions++;
        this->table[index].insert(this->table[index].begin(), value);
    }
    else{
        this->table[index][0] = value;
    }
}

// Public Methods
void HashTable::insert(int num){
    int index = getHash(num, this->table.size());
    // Increment the number of collisions
    switch(this->mode){
        // Linear Probing
        case 0:{
            linearProbe(num);
            break;
        }
        // Double Hashing
        case 1:{
            doubleHash(num);
            break;
        }
        // Separate Chaining
        case 2:{
            chaining(num);
            break;
        }
    }
    // There is no collision, so insert at index
    this->amountFilled++;
}

void HashTable::print_table(){
    if(this->mode != 2){
        for(int i = 0; i < this->table.size(); i++){
            string valOutput;
            for(int value : this->table[i]){
                valOutput += to_string(value) + " ";
            }
            cout << i << ": " << valOutput << endl;
            valOutput = "";
        }
        
    }
    else{
        for(int i = 0; i < this->table.size(); i++){
            string valOutput;
            for(int value : this->table[i]){
                valOutput += to_string(value) + " ";
            }
            if(stoi(valOutput) == 0){
                cout << i << ": " << endl;
            }
            else{
                cout << i << ": " << valOutput << endl;
            }
            valOutput = "";
        }
    }
}

int HashTable::get_num_collisions(){
    return this->collisions;
}