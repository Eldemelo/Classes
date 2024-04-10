#include "set_map.h"





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
    string line, sLine, sLine2;
    // Skip over the first line
    getline(readData, line);
    while(getline(readData, line)){
        istringstream ssLine(line);
        // skip to the 4th value (country)
        for(int i = 0; i <= 3; i++){
            getline(ssLine, sLine, ',');
        }
        // If the country has a split, read the second part and combine
        if(sLine[0] == '"'){
            string doubleCountry;
            getline(ssLine, sLine2, ',');
            for(int i = 1; i < sLine.size(); i++){
                doubleCountry += sLine[i];
            }
            doubleCountry += ", ";
            for(int i = 1; i < sLine2.size() - 1; i++){
                doubleCountry += sLine2[i];
            }
            countrySet.insert(doubleCountry);
            continue;
        }
        // insert the country to the set
        countrySet.insert(sLine);
    }
    // Close the dataset reading
    readData.close();

    // Open the commands file
    ifstream commands(commandList);
    while(getline(commands, line)){
        istringstream ssLine(line);
        getline(ssLine, sLine, ' ');
        // Get the set or map
        if(sLine == "set"){
            getline(ssLine, sLine, ' ');
            countrySet.find(sLine) != countrySet.end() ? cout << 1 << endl : cout << 0 << endl;
        }
        else if(sLine == "map"){
            getline(ssLine, sLine, ' ');
            cout << 0 << endl;
        }
        
    }


    // Print every value in the set
    for(set<string>::iterator mySet = countrySet.begin(); mySet != countrySet.end(); mySet++){
        cout << *mySet << ";";
    }
}