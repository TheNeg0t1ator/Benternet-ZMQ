#include <cstdio>
#include <vector>
#include "cJSON.h"
#ifndef FILECLASS_H
#define FILECLASS_H

class FileClass
{
public:
    FileClass();
    bool openFile();
    void closeFile();
    bool readFile();
    std::vector<int> outputprimes();
private:
    FILE *file;
    std::vector<int> primelist;
};

#endif // FILECLASS_H
