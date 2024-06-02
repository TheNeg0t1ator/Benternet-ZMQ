#include "fileclass.h"
#include <iostream>
#include <fstream>

FileClass::FileClass() : file(nullptr) {}

bool FileClass::openFile(std::string filename){
    this->filename = filename; // store the filename
    file = fopen(filename.c_str(), "r");
    if (file == NULL){
        perror("Error opening file");
        return false;
    } else {
        return true;
    }
}

void FileClass::closeFile(){
    if (file) {
        
        fclose(file);
        
        file = nullptr;
    }
}

bool FileClass::readFile(){
    if (filename.empty()) {
        return false;
    }
    std::string line;
    std::ifstream inputFile(filename); // Use the filename directly i
    if (!inputFile.is_open()) {
        perror("Error opening file");
        return false;
    }
    while (std::getline(inputFile, line)) { // Use std::getline with std::ifstream
        Numberlist.push_back(line);
    }
    return true;
}

std::vector<std::string> FileClass::outputNumbers(){
    return Numberlist;
}

