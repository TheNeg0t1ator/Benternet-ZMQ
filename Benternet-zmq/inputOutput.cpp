#include "inputOutput.h"
#include "cJSON.h"
#include <cstring>
#include <iostream>
#include <bitset>

#define Use_RuntimeError

inputOutput::inputOutput() {}

void inputOutput::inputJSON(std::string input)
{
    // std::cout << "entered inputJSON" << std::endl;

    inputData = stripToJson(input);
    // std::cout << "Stripped to json" << std::endl;
    // std::cout << "Input: " << input << std::endl;
    data = parseInput(inputData);
    // std::cout << "Data parsed" << std::endl;
}

inputData_t inputOutput::getInput(void)
{
    return data;
}

void cleardata(void)
{
    inputData_t data = {};
    std::string inputData = "";
    outputData_t output_struct = {};
    std::string outputData = "";
}

inputData_t inputOutput::parseInput(std::string input)
{
    // std::cout << "entered parseInput" << std::endl;
    // std::cout << "Input: " << input << std::endl;
    PrompData_t data;
    cJSON *root = cJSON_Parse(input.c_str());
    cJSON *prompt = cJSON_GetObjectItem(root, "Prompt");
    cJSON *resolution = cJSON_GetObjectItem(root, "resolution");
    cJSON *RequestType = cJSON_GetObjectItem(root, "RequestType");
    cJSON *numberType = cJSON_GetObjectItem(root, "numberType");
    std::string resolution_str;

    if (prompt != nullptr)
    {
        data.Prompt = prompt->valuestring;
    }
    else
    {
#ifdef Use_RuntimeError
        throw std::runtime_error("Error: Failed to parse input JSON. Missing \"Prompt\" field.");
#else
        inputData_t ErrorData;
        ErrorData.data = data;
        ErrorData.errorType = io_promptError;
        return ErrorData;
#endif
    }

    if (RequestType != nullptr)
    {
        std::string requeststring = RequestType->valuestring;
        if (strcmp(requeststring.c_str(), "Image") == 0)
        {
            data.RequestType = Request_image;
        }
        else if (strcmp(requeststring.c_str(), "Number") == 0)
        {
            data.RequestType = Request_number;
        }else if (strcmp(requeststring.c_str(), "Card") == 0){
            data.RequestType = Request_Card;
        }else{
            data.RequestType = 0;
            throw std::runtime_error("Error: Failed to parse input JSON. Invalid \"RequestType\" field.");
        }
    }
    else
    {
#ifdef Use_RuntimeError
        throw std::runtime_error("Error: Failed to parse input JSON. Missing \"RequestType\" field.");
#else
        inputData_t ErrorData;
        ErrorData.data = data;
        ErrorData.errorType = io_requestTypeError;
        return ErrorData;
#endif
    }

    if (data.RequestType == Request_image)
    {
        if (resolution != nullptr)
        {
            resolution_str = resolution->valuestring;
        }
        else
        {
#ifdef Use_RuntimeError
            throw std::runtime_error("Error: Failed to parse input JSON. Missing \"resolution\" field.");
#else
            inputData_t ErrorData;
            ErrorData.data = data;
            ErrorData.errorType = io_resolutionError;
            return ErrorData;
#endif
        }
        sscanf(resolution_str.c_str(), "%hdx%hd", &data.resolution.x, &data.resolution.y);
    }
    else if (data.RequestType == Request_number)
    {
        if (numberType != nullptr)
        {
            std::string NumbertypeString = numberType->valuestring;
            std::cout << "parse input NumberType: " << NumbertypeString << std::endl;
            if (strcmp(NumbertypeString.c_str(), "Prime") == 0){
                data.numberType = Number_Type_Prime;
            }else if (strcmp(NumbertypeString.c_str(), "Simple") == 0){
                data.numberType = Number_Type_Simple;
            }else if (strcmp(NumbertypeString.c_str(), "Fibonacci") == 0){
                data.numberType = Number_Type_Fibonacci;
            }else{
                data.numberType = 0;
                throw std::runtime_error("Error: Failed to parse input JSON. Invalid \"numberType\" field.");
            }
            std::cout << "parse input NumberType: " << std::bitset<8>(data.numberType) << std::endl;

        }
        else
        {
            data.numberType = 0;

#ifdef Use_RuntimeError
            throw std::runtime_error("Error: Failed to parse input JSON. Missing \"numberType\" field.");
#else
            inputData_t ErrorData;
            ErrorData.data = data;
            ErrorData.errorType = io_numberTypeError;
            return ErrorData;
#endif
        }
    }
    //std::cout << "parsed input" << std::endl;
    cJSON_Delete(root);
    inputData_t output;
    output.errorType = io_NoError;
    output.data = data;
    return output;
}

std::string inputOutput::parseOutput(outputData_t input)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *prompt = cJSON_CreateString(input.data.Prompt.c_str());
    cJSON *RequestType = cJSON_CreateString(requestTypeToString(input.data.RequestType).c_str());
    cJSON *output = cJSON_CreateString(input.output.c_str());
    cJSON *errorType = cJSON_CreateNumber(input.errorType);

    cJSON_AddItemToObject(root, "Prompt", prompt);
    cJSON_AddItemToObject(root, "RequestType", RequestType);
    cJSON_AddItemToObject(root, "output", output);
    cJSON_AddItemToObject(root, "errorType", errorType);

    if (input.data.RequestType == Request_image)
    {
        cJSON *resolution = cJSON_CreateObject();
        cJSON *x = cJSON_CreateNumber(input.data.resolution.x);
        cJSON *y = cJSON_CreateNumber(input.data.resolution.y);
        cJSON_AddItemToObject(root, "resolution", resolution);
        cJSON_AddItemToObject(resolution, "x", x);
        cJSON_AddItemToObject(resolution, "y", y);
    }
    else if (input.data.RequestType == Request_number)
    {
        cJSON *number = cJSON_CreateNumber(input.number);
        cJSON *numberType = cJSON_CreateNumber(input.data.numberType);
        cJSON_AddItemToObject(root, "number", number);
        cJSON_AddItemToObject(root, "numberType", numberType);
    }else if(input.data.RequestType == Request_Card){
        // std::string suitString = input.card.outputsuitString();
        // int valueInt = input.card.getValue();
        // cJSON *card = cJSON_CreateObject();
        // cJSON *suit = cJSON_CreateString(suitString.c_str());
        // cJSON *rank = cJSON_CreateNumber(valueInt);
        // cJSON_AddItemToObject(card, "suit", suit);
        // cJSON_AddItemToObject(card, "rank", rank);
        // cJSON_AddItemToObject(root, "card", card);
    }

    char *output_string = cJSON_Print(root);
    std::string output_string_str(output_string);
    cJSON_Delete(root);
    return output_string_str;
}

std::string inputOutput::getOutput(outputData_t input)
{
    std::string output_string = parseOutput(input);
    return output_string;
}

void inputOutput::printinData(inputData_t data)
{
    printPrompt(data.data);
}

void inputOutput::printoutData(outputData_t data)
{
    std::cout << "Output: " << data.output << std::endl;
    std::cout << "Number: " << data.number << std::endl;
    std::cout << "ErrorType: " << data.errorType << std::endl;
    printPrompt(data.data);
}

void inputOutput::printResolution(resolution_t data)
{
    std::cout << "Resolution: " << data.x << "x" << data.y << std::endl;
}

void inputOutput::printPrompt(PrompData_t data)
{
    std::cout << "Prompt: " << data.Prompt << std::endl;
    printResolution(data.resolution);
    std::cout << "RequestType: " << data.RequestType << std::endl;
    std::cout << "numberType: " << data.numberType << std::endl;
}

void inputOutput::printData(void)
{
    printinData(data);
    std::cout << "InputData: " << inputData << std::endl;
    printoutData(output_struct);
    std::cout << "OutputData: " << outputData << std::endl;
}

std::string inputOutput::stripToJson(const std::string &input)
{
    // Find the first occurrence of '{'
    size_t start = input.find('{');
    if (start == std::string::npos)
    {
        // If there's no '{', return an empty string (no JSON found)
        return "";
    }

    // Find the last occurrence of '}'
    size_t end = input.rfind('}');
    if (end == std::string::npos)
    {
        // If there's no '}', return an empty string (no JSON found)
        return "";
    }

    // Extract the JSON substring
    std::string jsonStr = input.substr(start, end - start + 1);
    // std::cout << "Stripped JSON: " << jsonStr << std::endl;
    return jsonStr;
}


std::string inputOutput::requestTypeToString(uint8_t requestType){
    if(requestType == Request_image){
        return "Image";
    }else if(requestType == Request_number){
        return "Number";
    }else{
        return "";
    }
}