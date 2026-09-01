#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/stat.h>

std::string logDir = "logFolder/";
std::string prefix = "inkling";
std::vector<std::string> fileNames;

void getFiles(){
    int fileCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(logDir)) {
        if (entry.is_regular_file()) { // Ensure it's a regular file
            std::string filename = entry.path().filename().string();

            // Check if the filename starts with the prefix
            if (filename.find(prefix) == 0) {
                fileNames.push_back(filename);
                // std::cout << "found file: " << filename << std::endl;
            }
        }
    }
}

void sort(std::string fileName){
    std::vector<std::string> lines;
    std::ifstream inFile(logDir + fileName);
    std::string currLine;
    while(std::getline(inFile, currLine)){
        lines.push_back(currLine);
    }
    inFile.close();

    std::sort(lines.begin(), lines.end());

    std::ofstream outFile(logDir + fileName);
    for (auto& sortedLine : lines){
        outFile << sortedLine << std::endl;
    }
    // std::cout << "file sorted" << std::endl;
    outFile.close();
}

void createLogsDir(){
	std::string logDir = "logFolder";
	(std::filesystem::create_directory(logDir));
}

int main(int argc, char* argv[]){
    std::string fileName = "actions.txt";
    createLogsDir();
    getFiles();
    if (!std::filesystem::exists(logDir)) {
        std::cout << "Directory does not exist: " << logDir << std::endl;
        return 1;
    }
    
    // Compile all file text to a single file
    std::ofstream outFile(logDir + fileName);
    for(auto file : fileNames){
        // std::cout << "opening file: " << file << std::endl;
        std::ifstream inFile(logDir + file);
        std::string line;
        while(std::getline(inFile, line)){
            outFile << line << '\n';
        }
        inFile.close();
    }
    outFile.close();

    // Set file permissions after closing the file
    chmod((logDir + fileName).c_str(), 0755);

    // Perform sorting of file
    sort(fileName);

    return 0;
}