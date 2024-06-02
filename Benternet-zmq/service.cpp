#include <iostream>
#include <zmq.hpp>
#include "zmq_service.h"
#include "fileclass.h"
#include "inputOutput.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

inputOutput io_class;


int main( void )
{
    std::vector<int> primes;
    FileClass file;
    if (file.openFile())
    {
        file.readFile();
        primes = file.outputprimes();
        file.closeFile();
    }
    else
    {
        std::cout << "File not found." << std::endl;
    }
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
            std::cout << "while ";
            messageReceived = service.receive(1000); // Receive a message
            sleep(1000);

            if (messageReceived.find("kobe?") != std::string::npos)
            {
                std::cout << "Received message: " << messageReceived << std::endl;
                
                //io_class.cleardata();
                io_class.inputJSON(messageReceived.substr(5));
                std::cout << "Data received: " << std::endl;
                io_class.printData();
    
                inputData_t data = io_class.getInput();
                outputData_t output_struct;
                output_struct.data = data.data;
                output_struct.errorType = 0;
                output_struct.number = 0;
                output_struct.output = "I am here";
                std::string output = io_class.getOutput(output_struct);
                
                
                std::string message = "kobe!>" + output;
                service.send(message.c_str());
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
