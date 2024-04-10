#include "set_map.h"



string getCurrCol(istringstream *ss, string sLine){
    bool closed = false;
    string currCol;
    while((*ss).peek() != '"'){
        currCol += (*ss).get();
    }
    return currCol;
}

int main(int argc, char* argv[]){
    // Arguments are <dataset> <command_list>
    string dataSet = argv[1];
    string commandList = argv[2];

    // Create set to hold countries
    set<string> countrySet;
    // map<dataTypeForKey, dataTypeForValue> name;
    map<string, string> countryMap;
    map<string, map<string, string>> nestedMap;

    // Read from a file
    ifstream readData(dataSet);
    string currLine, sLine;
    // Skip over the first line
    getline(readData, currLine);
    while(getline(readData, currLine)){
        // cout << "Next line" << endl;
        istringstream ss(currLine);
        int col = 0;
        string country;
        while(getline(ss, sLine, ',')){
            col++;
            if(ss.peek() == '"'){
                ss.get();
                country = getCurrCol(&ss, sLine);
                if(col == 3){
                    countrySet.insert(country);
                    break;
                }
            }
            else if(col == 4){
                countrySet.insert(sLine);
                break;
            }
        }
    }
    // Close the dataset reading
    readData.close();

    // Open the commands file
    ifstream commands(commandList);
    while(getline(commands, sLine)){
        istringstream ssLine(sLine);
        getline(ssLine, sLine, ' ');
        // Get the set or map
        if(sLine == "set"){
            getline(ssLine, sLine, '\n');
            countrySet.find(sLine) != countrySet.end() ? cout << 1 << endl : cout << 0 << endl;
        }
        else if(sLine == "map"){
            getline(ssLine, sLine, ' ');
            cout << 0 << endl;
        } 
    }


    cout << endl << "Set" << endl;
    // Print every value in the set
    for(set<string>::iterator mySet = countrySet.begin(); mySet != countrySet.end(); mySet++){
        cout << *mySet << endl;
    }
}