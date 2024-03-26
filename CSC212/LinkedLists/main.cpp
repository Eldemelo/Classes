#include "linked_list.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

// Compile command:
// g++ main.cpp linked_list.cpp node.cpp -o prog
// CLAs being tested:
// ./prog ./data/test1.txt
// ./prog ./data/test2.txt
// ./prog ./data/test3.txt
// ./prog ./data/test4.txt
// ./prog ./data/test5.txt
// ./prog ./data/test6.txt

int main(int argc, char* argv[]){
    // Read from the file passed in the CLA
    string fileName = argv[1];
    // Open file and read line
    ifstream inFile(fileName);
    // Read each line and append them to different strings
    // Get the first line and determine if it's data or a command
    string currLine;
    getline(inFile, currLine);
    stringstream currLineStream(currLine);
    string tempVal;
    int count = 0;
    // Counts the number of values in the first line
    while(getline(currLineStream, tempVal, ' ')){
        count++;
    }

    // Declare LinkedList for instantiation
    LinkedList myList;
    // Check if it's a command or data and use the proper constructor
    // Instantiate empty constructor
    if(count == 0){
        myList = LinkedList();
    }
    // Instantiate constructor with first command
    else if(count == 1 || count == 2){
        myList = LinkedList(stoi(currLine));
    }
    // Instantiate constructor with data
    else if(count > 2){
        currLineStream = stringstream(currLine);
        vector<int> dataVector; 
        while(getline(currLineStream, tempVal, ' ')){
            dataVector.push_back(stoi(tempVal));
        }
        myList = LinkedList(dataVector);
    }


    cout << myList.to_string() << endl;
    // While there are still commands in the file
    while(getline(inFile, currLine)){
        //cout << "Current command: " << currLine << endl;
        // Convert string to stringStream
        string currVal;
        // Determine which command to perform
        if(currLine.find('?') != string::npos){
            // Remove the question mark
            for(int i = 0; i < currLine.length() - 1; i++){
                currVal += currLine[i];
            }
            cout << myList.contains(stoi(currVal)) << endl;
        }
        else if(currLine.find('-') != string::npos){
            // Remove the negative
            for(int i = 1; i < currLine.length(); i++){
                // cout << currLine[i];
                currVal += currLine[i];
            }
            myList.remove(stoi(currVal));
            cout << myList.to_string() << endl;
        }
        else if(currLine.find(' ') != string::npos){
            vector<int> tempVector;
            stringstream currLineStream(currLine);
            while(getline(currLineStream, tempVal, ' ')){
                tempVector.push_back(stoi(tempVal));
            }
            myList.insert(tempVector[0], tempVector[1]);
            cout << myList.to_string() << endl;
        }
        else{
            // Even integer
            if(stoi(currLine) % 2 == 0){
                myList.push_back(stoi(currLine));
            }
            // Odd integer
            else{
                myList.push_front(stoi(currLine));
            }
            cout << myList.to_string() << endl;
        }
    }
    inFile.close();
}