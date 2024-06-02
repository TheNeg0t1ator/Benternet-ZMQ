#include "inputOutput.h"
#include "cJSON.h"
#include <iostream>

inputOutput::inputOutput() {}

void inputOutput::inputJSON(std::string input)
{
    std::cout << "entered inputJSON" << std::endl;
    inputData = input;
    std::cout << "Input: " << input << std::endl;
    data = parseInput(input);
    std::cout << "Data parsed" << std::endl;
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
    std::cout << "entered parseInput" << std::endl;
    PrompData_t data;
    cJSON *root = cJSON_Parse(input.c_str());
    cJSON *prompt = cJSON_GetObjectItem(root, "Prompt");
    cJSON *resolution = cJSON_GetObjectItem(root, "resolution");
    cJSON *RequestType = cJSON_GetObjectItem(root, "RequestType");
    cJSON *numberType = cJSON_GetObjectItem(root, "numberType");
    std::string resolution_str;
    
    if (prompt != nullptr) {
        data.Prompt = prompt->valuestring;
    } else {
        throw std::runtime_error("Error: Failed to parse input JSON. Missing \"Prompt\" field.");
    }

    if (resolution != nullptr) {
        resolution_str = resolution->valuestring;
    } else {
        throw std::runtime_error("Error: Failed to parse input JSON. Missing \"resolution\" field.");
    }

    sscanf(resolution_str.c_str(), "%dx%d", &data.resolution.x, &data.resolution.y);


    if (RequestType != nullptr) {
        data.RequestType = RequestType->valueint;
    } else {
        throw std::runtime_error("Error: Failed to parse input JSON. Missing \"RequestType\" field.");
    }

    if (numberType != nullptr) {
        data.numberType = numberType->valueint;
    } else {
        data.numberType = 0;
        //throw std::runtime_error("Error: Failed to parse input JSON. Missing \"numberType\" field.");
    }
    std::cout << "parsed input" << std::endl;
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
