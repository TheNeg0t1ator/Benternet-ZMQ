#ifndef FILECLASS_H
#define FILECLASS_H

#include <vector>
#include <string>
#include <cstdio>

class FileClass {
public:
    FileClass();
    bool openFile(std::string filename);
    void closeFile();
    bool readFile();
    std::vector<std::string> outputNumbers();

private:
    FILE* file;
    std::string filename; // store the filename
    std::vector<std::string> Numberlist;
};

#endif
