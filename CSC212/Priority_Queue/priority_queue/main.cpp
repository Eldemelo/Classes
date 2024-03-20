#include "priority_queue.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

    Priority_Queue* priority_queue;
    string file_name(argv[1]);

	vector<int> file_data;
    vector<int> priority;
    string line;

	ifstream file(file_name);

    // Read the first line from the file & store into vector
    getline(file, line);

    stringstream ss(line);

    int temp_int;
    while(ss >> temp_int){
        file_data.push_back(temp_int);
        priority.push_back(priority.size());
    }

    // Create a priority_queue based on what was in the first line of the file
    if(file_data.size() == 0){
        priority_queue = new Priority_Queue();
    }else if (file_data.size() == 1){
        priority_queue = new Priority_Queue(file_data[0], priority[0]);
    }else{
        priority_queue = new Priority_Queue(file_data, priority);
    }

    cout << priority_queue->to_string() << endl;

    // Continue to read through the file
    while(getline(file, line)){

        // Check the first value 
        if(line[0] == '-' && line.size() == 1){
            // remove first value in list
            priority_queue->remove();
            // Print list
            cout << priority_queue->to_string() << endl;
        }
        else if(line[0] == '?'){
            // Print first value in list
            cout << priority_queue->peek() << endl;
        }
        else{
            // Convert string to stringstream to split value and priority
            istringstream currStringStream(line);
            // Parse string into 2 variables
            string currVal, currPriority;
            currStringStream >> currVal;
            currStringStream >> currPriority;
            // push back new value to list
            priority_queue->push_back(stoi(currVal), stoi(currPriority));
            // print new line
            cout << priority_queue->to_string() << endl;
        }
    }
    // close file
    file.close();
}