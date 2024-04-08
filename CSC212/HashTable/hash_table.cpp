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
vector<vector<int>> HashTable::resize_table(){
    this->size *= 2;
    vector<vector<int>> temp(this->size, vector<int>(1,0));
    for(vector<int> row : this->table){
        for(int val : row){
            if(val != 0){
                temp = resizeInsert(val, temp);
            }
        }
    }
    return temp;
}

// Helper method for resize table
vector<vector<int>> HashTable::resizeInsert(int num, vector<vector<int>> temp){
    // If the table is 70% or more full
    int index = getHash(num, this->size);
    // We have a collision
    if(temp[index][0] != 0){
        // Increment the number of collisions
        this->collisions++;
        switch(this->mode){
            // Linear Probing
            case 0:{
                temp = linearProbe(num, index, temp);
                break;
            }
            // Double Hashing
            case 1:{
                int index = getDoubleHash(num, this->size);
                temp[index][0] = num;
                break;
            }
            // Separate Chaining
            case 2:{
                int index = getHash(num, this->size);
                temp[index].push_back(num);
                break;
            }
        }
    }
    // There is no collision, so insert at index
    else{
        temp[index][0] = num;
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
vector<vector<int>> HashTable::linearProbe(int value, int index, vector<vector<int>> temp){
    int original = index;
    do{
        if(index == temp.size()){
            index = 0;
            continue;
        }
        // Thix index is empty so insert here
        if(temp[index][0] == 0){
            temp[index][0] = value;
            return temp;
        }
        // Increment the index by 1;
        index++;
    }
    while(index != original);

    return temp;
}

// Public Methods
void HashTable::insert(int num){
    // Check if there is a collision
    int index = getHash(num, this->size);
    if(this->table[index][0] != 0){
        this->collisions++; 
    }
    
    bool resized = false;
    // If the table is 70% or more full
    if((this->amountFilled * 1.0) / this->size >= 0.7){
        this->table = resize_table();
        resized = true;
    }

    index = getHash(num, this->size);
    // We have a collision
    if(this->table[index][0] != 0){
        if(resized){
            this->collisions++;
        }
        // Increment the number of collisions
        switch(this->mode){
            // Linear Probing
            case 0:{
                this->table = linearProbe(num, index, this->table);
                break;
            }
            // Double Hashing
            case 1:{
                int index = getDoubleHash(num, this->size);
                this->table[index][0] = num;
                break;
            }
            // Separate Chaining
            case 2:{
                int index = getHash(num, this->size);
                this->table[index].push_back(num);
                this->collisions--;
                break;
            }
        }
    }
    // There is no collision, so insert at index
    else{
        this->table[index][0] = num;
    }
    this->amountFilled++;
}

void HashTable::print_table(){
    if(this->mode != 2){
        for(int i = 0; i < this->size; i++){
            string valOutput;
            for(int value : this->table[i]){
                valOutput += to_string(value) + " ";
            }
            cout << i << ": " << valOutput << endl;
            valOutput = "";
        }
        
    }
    else{
        for(int i = 0; i < this->size; i++){
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