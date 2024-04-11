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
    map<string, map<string, int>> nestedMap;

//MARK: SET
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

//MARK: SINGLE MAP
    // Re-open file for maps
    ifstream readMapData(dataSet);
    // Skip over the first line
    getline(readMapData, currLine);
    while(getline(readMapData, currLine)){
        istringstream ss(currLine);
        int col = 0;
        string country;
        string saveCountry;
        while(getline(ss, sLine, ',')){
            col++;
            if(ss.peek() == '"'){
                ss.get();
                col++;
                country = getCurrCol(&ss, sLine);
                getline(ss, sLine, ',');
                if(col == 4){
                    // Save the country for future parsing
                    saveCountry = country;
                }
            }
            else if(col == 4){
                // Check if it has an asterick
                saveCountry = sLine;
            }
            else if(col == 8){
                // If the country already exists
                if(countryMap.find(saveCountry) != countryMap.end()){
                    countryMap[saveCountry] += stoi(sLine);
                }
                else{
                    countryMap.insert({saveCountry, stoi(sLine)});
                }
            }
        }
    }
    readMapData.close();

//MARK: NESTED MAP
    // Re-open file for maps
    ifstream readNestedData(dataSet);
    // Skip over the first line
    getline(readNestedData, currLine);
    while(getline(readNestedData, currLine)){
        istringstream ss(currLine);
        int col = 0;
        string country;
        string saveCountry;
        while(getline(ss, sLine, ',')){
            col++;
            if(ss.peek() == '"'){
                ss.get();
                col++;
                country = getCurrCol(&ss, sLine);
                getline(ss, sLine, ',');
                if(col == 4){
                    // Save the country for future parsing
                    saveCountry = country;
                }
            }
            else if(col == 4){
                // Check if it has an asterick
                saveCountry = sLine;
            }
            else if(col == 8){
                // If the country already exists
                if(countryMap.find(saveCountry) != countryMap.end()){
                    countryMap[saveCountry] += stoi(sLine);
                }
                else{
                    countryMap.insert({saveCountry, stoi(sLine)});
                }
            }
        }
    }
    readNestedData.close();

    // Push all values from the set to the map
    for(set<string>::iterator mySet = countrySet.begin(); mySet != countrySet.end(); mySet++){
        countryMap.insert({*mySet, 0});
    }

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
            getline(ssLine, sLine, '\n');
            // Determine if the map contains a semi-colon
            bool semicolon = false;
            for(int i = 0; i < sLine.size(); i++){
                if(sLine[i] == ';') semicolon = true;
            }
            // State type
            if(semicolon){

            }
            // Non-state type
            else{
                countryMap.find(sLine) != countryMap.end() ?
                cout << countryMap[sLine] << endl : cout << -1 << endl;
            }
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