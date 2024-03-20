#include "queue.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

    Queue* queue;
    string file_name(argv[1]);

	vector<int> file_data;
    string line;

	ifstream file(file_name);

    // Read the first line from the file & store into vector
    getline(file, line);

    stringstream ss(line);

    int temp_int;
    while(ss >> temp_int){
        file_data.push_back(temp_int);
    }

    // Create a queue based on what was in the first line of the file
    if(file_data.size() == 0){
        queue = new Queue();
    }else if (file_data.size() == 1){
        queue = new Queue(file_data[0]);
    }else{
        queue = new Queue(file_data);
    }

    cout << queue->to_string() << endl;

    // Continue to read through the file
    while(getline(file, line)){

        // Check the first value 
        if(line[0] == '-' && line.size() == 1){
            // remove first value in list
            queue->remove();
            // Print list
            cout << queue->to_string() << endl;
        }
        else if(line[0] == '?'){
            // Print first value in list
            cout << queue->peek() << endl;
        }
        else{
            // push back new value to list
            queue->push_back(stoi(line));
            // print new line
            cout << queue->to_string() << endl;
        }
    }
    // close file
    file.close();
}