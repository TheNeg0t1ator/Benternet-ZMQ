#include "fileclass.h"

FileClass::FileClass() {}

bool FileClass::openFile(){
    file = fopen("C:\\Users\\kobed\\Coding\\Cuda-prime-GIT\\output.txt", "r");
    if (file == NULL){
        perror("Error opening file");
        return false;
    }else{
        return true;
    }
}

void FileClass::closeFile(){
    fclose(file);
}


bool FileClass::readFile(){
    int prime;
    while (fscanf(file, "%d", &prime) != EOF){
        primelist.push_back(prime);
    }
    return true;
}


std::vector<int> FileClass::outputprimes(){
    return primelist;
}

