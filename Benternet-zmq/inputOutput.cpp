#include "inputOutput.h"
#include "cJSON.h"
#include <iostream>

inputOutput::inputOutput() {}

void inputOutput::inputJSON(std::string input)
{
    inputData = input;
    data = parseInput(input);
}

inputData_t inputOutput::getInput(void)
{
    return data;
}



void cleardata(void){
    inputData_t data = {};
    std::string inputData = "";
    outputData_t output_struct = {};
    std::string outputData = "";
}


inputData_t inputOutput::parseInput(std::string input){
    PrompData_t data;
    cJSON *root = cJSON_Parse(input.c_str());
    cJSON *prompt = cJSON_GetObjectItem(root, "Prompt");
    cJSON *resolution = cJSON_GetObjectItem(root, "resolution");
    cJSON *RequestType = cJSON_GetObjectItem(root, "RequestType");
    cJSON *numberType = cJSON_GetObjectItem(root, "numberType");
    cJSON *x = cJSON_GetObjectItem(resolution, "x");
    cJSON *y = cJSON_GetObjectItem(resolution, "y");
    data.Prompt = prompt->valuestring;
    data.resolution.x = x->valueint;
    data.resolution.y = y->valueint;
    data.RequestType = RequestType->valueint;
    data.numberType = numberType->valueint;
    cJSON_Delete(root);
    inputData_t output;
    output.data = data;
    return output;
}

std::string inputOutput::parseOutput(outputData_t input){
    cJSON *root = cJSON_CreateObject();
    cJSON *prompt = cJSON_CreateString(input.data.Prompt.c_str());
    cJSON *resolution = cJSON_CreateObject();
    cJSON *RequestType = cJSON_CreateNumber(input.data.RequestType);
    cJSON *numberType = cJSON_CreateNumber(input.data.numberType);
    cJSON *x = cJSON_CreateNumber(input.data.resolution.x);
    cJSON *y = cJSON_CreateNumber(input.data.resolution.y);
    cJSON *number = cJSON_CreateNumber(input.number);
    cJSON *output = cJSON_CreateString(input.output.c_str());
    cJSON *errorType = cJSON_CreateNumber(input.errorType);
    cJSON_AddItemToObject(root, "Prompt", prompt);
    cJSON_AddItemToObject(root, "resolution", resolution);
    cJSON_AddItemToObject(root, "RequestType", RequestType);
    cJSON_AddItemToObject(root, "numberType", numberType);
    cJSON_AddItemToObject(resolution, "x", x);
    cJSON_AddItemToObject(resolution, "y", y);
    cJSON_AddItemToObject(root, "number", number);
    cJSON_AddItemToObject(root, "output", output);
    cJSON_AddItemToObject(root, "errorType", errorType);
    char *output_string = cJSON_Print(root);
    std::string output_string_str(output_string);
    cJSON_Delete(root);
    return output_string_str;
}

 
std::string inputOutput::getOutput(outputData_t input){
    std::string output_string = parseOutput(input);
    return output_string;
}

void inputOutput::printinData(inputData_t data){
    printPrompt(data.data);
}

void inputOutput::printoutData(outputData_t data){
    std::cout << "Output: " << data.output << std::endl;
    std::cout << "Number: " << data.number << std::endl;
    std::cout << "ErrorType: " << data.errorType << std::endl;
    printPrompt(data.data);
}

void inputOutput::printResolution(resolution_t data){
    std::cout << "Resolution: " << data.x << "x" << data.y << std::endl;
}

void inputOutput::printPrompt(PrompData_t data){
    std::cout << "Prompt: " << data.Prompt << std::endl;
    printResolution(data.resolution);
    std::cout << "RequestType: " << data.RequestType << std::endl;
    std::cout << "numberType: " << data.numberType << std::endl;
}

void inputOutput::printData(void){
    printinData(data);
    std::cout << "InputData: " << inputData << std::endl;
    printoutData(output_struct);
    std::cout << "OutputData: " << outputData << std::endl;
}