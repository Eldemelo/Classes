#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main(int argc, char*argv[]){
    string fileName;
    double scaling_factor;
    int capacity;
    int length;
    int initialVal;
    if (argc == 2){
        fileName = argv[1];
    }
    else if(argc == 4){
        fileName = argv[1];
        scaling_factor = stod(argv[2]);
        capacity = stoi(argv[3]);
    }
    else if(argc == 5){
        fileName = argv[1];
        scaling_factor = stod(argv[2]);
        length = stoi(argv[3]);
        initialVal = stoi(argv[4]);
    }

    // Append numbers from txt file to temp vector
    ifstream inputFile(fileName);
    vector<int> fileData;
    string tempVal;
    while (inputFile >> tempVal){
        fileData.push_back(stoi(tempVal));
    }
    inputFile.close();

    // Do something with fileData vector
    // Create a dynamicArray object
    DynamicArray dynamicArray;
    if(argc == 4){
        dynamicArray = DynamicArray(scaling_factor, capacity);
    }
    else if(argc == 5){
        dynamicArray = DynamicArray(scaling_factor, length, initialVal);
    }
    else{
        dynamicArray = DynamicArray();
    }
    // Append half the values from the file to the dynamic array
    for(int i = 0; i < (fileData.size() / 2); i++){
        dynamicArray.append(fileData[i]);
    }
    cout<< dynamicArray.to_string() << endl;

    // Prepend the second half of values to the dynamic array
    for(int i = (fileData.size() / 2); i < fileData.size(); i++){
        dynamicArray.prepend(fileData[i]);
    }
    cout <<  dynamicArray.to_string() << endl;

    // Find the first of the value 1/3 of the way though the original list
    int numToFind = fileData[fileData.size() / 3];
    bool found = false;
    unsigned int index;
    found = dynamicArray.find_first_of(numToFind, &index);
    cout << found << "\t" << index << endl;

    // Find the last of the value 1/3 of the way through the original list
    numToFind = fileData[fileData.size() / 3];
    found = false;
    found = dynamicArray.find_last_of(numToFind, &index);
    cout << found << "\t" << index << endl;

    // Remove last
    dynamicArray.remove_last();
    cout << dynamicArray.to_string() << endl;

    // Remove first
    dynamicArray.remove_first();
    cout << dynamicArray.to_string() << endl;

    // Clear
    dynamicArray.clear();
    cout << dynamicArray.to_string() << endl;

}