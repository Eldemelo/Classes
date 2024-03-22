#include "DynamicArray.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

// "Fancy" way to write a default constructor.
// Note: The other constructors can *NOT* be written this way!
DynamicArray::DynamicArray()
    : m_length(0), m_capacity(1), m_scaling_factor(2.0), m_data(new int[1]) {
}

DynamicArray::DynamicArray(double scaling_factor, unsigned int capacity) {
    this->m_length = 0;
    this->m_scaling_factor = scaling_factor;
    this->m_capacity = capacity;
    this->m_data = new int[capacity];
}


DynamicArray::DynamicArray(double scaling_factor, unsigned int length, int default_value) {
    this->m_scaling_factor = scaling_factor;
    this->m_capacity = length;
    this->m_length = length;
    this->m_data = new int[m_length];
    for(int i = 0; i < this->m_length; i++){
        this->m_data[i] = default_value;
    }
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    // use the assignment operator
    (*this) = other; 
}

// Destructor: destroys the dynamically allocated array on the heap
DynamicArray::~DynamicArray() {
    delete[] m_data;
}

unsigned int DynamicArray::get_length() {
    return m_length;
}

unsigned int DynamicArray::get_capacity() {
    return m_capacity;
}

double DynamicArray::get_scaling_factor() {
    return m_scaling_factor;
}

void DynamicArray::set_scaling_factor(double value) {
    m_scaling_factor = value;
}

string DynamicArray::to_string() {
	// Initialize an empty string
    string str("");
	for(int i = 0; i < this->m_length; i++){
        str += std::to_string(this->m_data[i]);
        str += " ";
    }
    return str;
}

bool DynamicArray::find_first_of(int value, unsigned int *index) {
    for (*index = 0; *index < this->m_length; (*index)++) {
        if (this->m_data[*index] == value) {
            return true;
        }
    }
    return false;
}

bool DynamicArray::find_last_of(int value, unsigned int *index) {
    for (*index = this->m_length - 1; *index >= 0; (*index)--) {
        if (this->m_data[*index] == value) {
            return true;
        }
    }
    return false;
}

void DynamicArray::append(int value) {
    if (this->m_length == this->m_capacity){
        int new_capacity = this->m_capacity * this->m_scaling_factor;
        int *new_array = new int[new_capacity];

        // Copy old data into new array
        for(int i = 0; i < this->m_length; i++){
            new_array[i] = this->m_data[i];
        }

        // Update the data and capacity
        this->m_data = new_array;
        this->m_capacity = new_capacity;
    }

    // Append value to array and increment length
    this->m_data[this->m_length] = value;
    this->m_length++;

}

void DynamicArray::prepend(int value) {
    // If there is no more memory, increase size of array
    if (this->m_length == this->m_capacity){
        int new_capacity = this->m_capacity * this->m_scaling_factor;
        this->m_capacity = new_capacity;
    }
    int *new_array = new int[m_capacity];
    // Assign the first value of new array to value
    new_array[0] = value;
    // Copy old data to new, larger array +1 index
    for(int i = 0; i < this->m_length; i++){
        new_array[i + 1] = m_data[i];
    }
    // Update old array with new info
    this->m_data = new_array;
    // Update the data and capacity
    this->m_length++;
}

void DynamicArray::remove_last() {
    if(this->m_length == 0){
        return;
    }
    this->m_length -= 1;
}

void DynamicArray::remove_first() {
    if(this->m_length == 0){
        return;
    }
    for(int i = 0; i < this->m_length - 1; i++){
        this->m_data[i] = this->m_data[i + 1];
    }
    this->m_length -= 1;
}

void DynamicArray::clear() {
    // Clear array from memory
    delete[] this->m_data;

    // Assign data pointer to null
    this->m_data = nullptr;

    // Clear capacity and size
    this->m_capacity = 0;
    this->m_length = 0;
}

// Examples of "operator overloading"
int& DynamicArray::operator[](unsigned int index) {
    return m_data[index];
}

DynamicArray& DynamicArray::operator=(const DynamicArray &other) {
    m_length = other.m_length;
    m_capacity = other.m_capacity;
    m_scaling_factor = other.m_scaling_factor;
    m_data = new int[m_capacity];
    memcpy(m_data, other.m_data, sizeof(int) * m_length);
    // this allows statements such as (a = b = c) assuming a, b, and c are all the DynamicArray type
    return (*this); 
}
