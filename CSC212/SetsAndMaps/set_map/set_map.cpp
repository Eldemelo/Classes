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
    map<string, int> countryMap;
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

    // Re-open file for maps
    ifstream readMapData(dataSet);
    // Skip over the first line
    getline(readMapData, currLine);
    while(getline(readMapData, currLine)){
        // cout << "Next line" << endl;
        istringstream ss(currLine);
        int col = 0;
        string country;
        string saveCountry;
        while(getline(ss, sLine, ',')){
            col++;
            if(ss.peek() == '"'){
                ss.get();
                country = getCurrCol(&ss, sLine);
                if(col == 3){
                    // Save the country for future parsing
                    saveCountry = country;
                }
            }
            else if(col == 4){
                saveCountry = sLine;
            }
            else if(col == 8){
                // If the country already exists
                if(countryMap.find(saveCountry) != countryMap.end()){
                    // cout << "hello" << endl;
                    countryMap[saveCountry] += stoi(sLine);
                }
                else{
                    // cout << "Does not exist: " << saveCountry << " " << sLine << endl;
                    countryMap.insert({saveCountry, stoi(sLine)});
                }
            }
        }
    }
    readMapData.close();

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
            // Determine if the map contains a semi-colon
            getline(ssLine, sLine, '\n');
            cout << countryMap[sLine] << endl;
        } 
    }


    // cout << endl << "Set" << endl;
    // // Print every value in the set
    // for(set<string>::iterator mySet = countrySet.begin(); mySet != countrySet.end(); mySet++){
    //     cout << *mySet << endl;
    // }

    // cout << endl << "Map" << endl;
    // // Print every value in the set
    // for(set<string>::iterator mySet = countrySet.begin(); mySet != countrySet.end(); mySet++){
    //     cout << countryMap[*mySet] << endl;
    // }
}