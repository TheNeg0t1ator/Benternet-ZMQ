#include <bitset>
#include <iostream>
#include <zmq.hpp>
#include "zmq_service.h"
#include "fileclass.h"
#include "inputOutput.h"
#include "cardclass.hpp"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

inputOutput io_class;
std::string fibboFile = "../numbers/fibonacci_sequence.txt";
std::string primeFile = "../numbers/primes.txt";

int main( void )
{
    std::vector<std::string> primes;
    std::vector<std::string> fibbo;
    FileClass fileprime;
    FileClass filefibbo;
    
    if (fileprime.openFile(primeFile))
    {
        fileprime.readFile();
        primes = fileprime.outputNumbers();
        fileprime.closeFile();
    }
    else
    {   
        fileprime.closeFile();
        std::cout << "File not found: "<< primeFile << std::endl;

    }

    if (filefibbo.openFile(fibboFile))
    {
        filefibbo.readFile();
        fibbo = filefibbo.outputNumbers();
        filefibbo.closeFile();
    }
    else
    {
        filefibbo.closeFile();
        std::cout << "File not found: "<< fibboFile << std::endl;
        
    }
    std::cout << "Fibonacci number 500 " << fibbo[499] << std::endl;
    std::cout << "Prime number 500 " << primes[499] << std::endl;

    std::cout << "Starting service..." << std::endl;
    try
    {
        ZMQ_service service("tcp://benternet.pxl-ea-ict.be:24041","tcp://benternet.pxl-ea-ict.be:24042" );
        //"tcp://192.168.1.8:24041"
        //"tcp://localhost:24041"
        //"tcp://benternet.pxl-ea-ict.be:24041"

        std::string messageReceived;
        if( service.connected() )
        {
            service.Subscribe("kobe");
        }
        std::cout << "Service started." << std::endl;

        while( service.connected() )
        {
            //std::cout << "while ";
            messageReceived = service.receive(1000); // Receive a message
            sleep(100);

            if (messageReceived.find("kobe?") != std::string::npos)
            {
                //std::cout << "Received message: " << messageReceived << std::endl;
                
                //io_class.cleardata();
                io_class.inputJSON(messageReceived);
                if(io_class.getInput().errorType != io_NoError)
                {
                    std::cout << "Error in input data, error : " << std::bitset<8>(io_class.getInput().errorType) << std::endl;
                    continue;
                }else{
                //std::cout << "Data received: " << std::endl;
                //io_class.printData();
    
                inputData_t data = io_class.getInput();
                outputData_t output_struct;
                output_struct.errorType = 0;
                //std::cout << "Request type: " << std::bitset<8>(data.data.RequestType) << std::endl;
                if(data.data.RequestType == Request_number)
                {
                    //std::cout << "Request number: "<< data.data.Prompt  << std::endl;
                    uint64_t number = std::stoull(data.data.Prompt, nullptr, 10);
                    
                    std::cout << "Numbertype: " << std::bitset<8>(data.data.numberType) << std::endl;
                    switch (data.data.numberType)
                    {
                    case Number_Type_Prime:
                        if (number <= primes.size()-1) {
                            output_struct.output = primes[number];
                            std::cout << "Prime number: " << output_struct.output << std::endl;
                        } else {
                            std::cout << "Invalid prime number index" << std::endl;
                            output_struct.errorType = io_outputError;
                        }
                        break;
                    case Number_Type_Fibonacci:
                        if (number <= fibbo.size()-1) {
                            output_struct.output = fibbo[number];
                            std::cout << "Fibonacci number: " << output_struct.output << std::endl;
                        } else {
                            std::cout << "Invalid Fibonacci number index" << std::endl;
                            output_struct.errorType = io_outputError;
                        }
                        std::cout << "Fibonacci number: " << output_struct.output << std::endl;
                        break;

                    default:
                        break;
                    }
                }else if (data.data.RequestType == Request_Card)
                {
                    output_struct.card = new CardClass(time(nullptr));
                    output_struct.output = output_struct.card->outputCardString();
                }
                
                output_struct.data = data.data;
                
                
                 
                
                output_struct.number = 0;
                //output_struct.output = "I am here";
                std::string output = io_class.getOutput(output_struct);
                
                
                std::string message = "kobe!>" + output;
                service.send(message.c_str());
                }
                sleep(100);
            }
            else
            {
                std::cout << "waiting for message...\n";
                
            }
        }

    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what() << std::endl;
        return 1; // Exit the program with an error code
    }
    catch( std::exception & ex )
    {
        std::cerr << "Caught an exception : " << ex.what() << std::endl;
        return 1; // Exit the program with an error code
    }
    catch( ... )
    {
        std::cerr << "Caught an unknown exception" << std::endl;
        return 1; // Exit the program with an error code
    }

    return 0;
}
