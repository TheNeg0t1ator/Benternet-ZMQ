#include <string>

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#define Request_image 1
#define Request_number 2
#define Number_Type_Prime 1
#define Number_Type_Simple 2
#define Number_Type_Fibonacci 3

#define io_NoError 0
#define io_parseError 1
#define io_promptError 2
#define io_resolutionError 3
#define io_requestTypeError 4
#define io_numberTypeError 5
#define io_numberError 6
#define io_outputError 7




typedef struct{
    uint16_t x;
    uint16_t y;

}resolution_t;

typedef struct{
    std::string Prompt;
    resolution_t resolution;
    uint8_t RequestType;
    uint8_t numberType;
}PrompData_t;

typedef struct{
    PrompData_t data;
    uint8_t errorType;
}inputData_t;

typedef struct{
    PrompData_t data;
    uint64_t number;
    std::string output;
    uint8_t errorType;
}outputData_t;

class  inputOutput
{
public:
    inputOutput();
    void inputJSON(std::string input);
    inputData_t getInput(void);
    std::string getOutput(outputData_t input);
    void cleardata(void);
    void printData(void);


private:
    inputData_t data;
    std::string inputData;
    outputData_t output_struct;
    std::string outputData;
    inputData_t parseInput(std::string input); //this function turns the json into data
    std::string parseOutput(outputData_t input); //this function turns the data back into json
    void printinData(inputData_t data);
    void printoutData(outputData_t data);
    void printResolution(resolution_t data);
    void printPrompt(PrompData_t data);
    std::string stripToJson(const std::string& input);
    std::string requestTypeToString(uint8_t requestType);
};

#endif // INPUTOUTPUT_H
