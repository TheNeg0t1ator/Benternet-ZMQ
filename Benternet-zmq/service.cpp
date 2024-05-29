#include <iostream>
#include <zmq.hpp>
#include "zmq_service.h"
#include "fileclass.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

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
    try
    {
        ZMQ_service service("tcp://benternet.pxl-ea-ict.be:24041","tcp://benternet.pxl-ea-ict.be:24042" );
        //"tcp://192.168.1.8:24041"
        //"tcp://localhost:24041"
        //"tcp://benternet.pxl-ea-ict.be:24041"
        std::string messageReceived;
        if( service.connected() )
        {
            service.Subscribe("kobe?");
        }
        
        
        while( service.connected() )
        {
            messageReceived = service.receive(1000); // Receive a message
            
            if (strcmp(messageReceived.c_str(), "kobe?") == 0)
            {

                sleep(100);
                std::string message = "kobe!>";

                service.send(message.c_str());
                
                
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
