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
    FileClass file;
    file.openFile();
    file.readFile();
    std::vector<int> primes = file.outputprimes();
    file.closeFile();
    try
    {
        ZMQ_service service("tcp://benternet.pxl-ea-ict.be:24041","tcp://benternet.pxl-ea-ict.be:24042" );
        //"tcp://192.168.1.8:24041"
        //"tcp://localhost:24041"
        //"tcp://benternet.pxl-ea-ict.be:24041"
        std::string messageReceived;
        if( service.connected() )
        {
            service.Subscribe("prime");
        }
        
        std::cout << "test1";

        while( service.connected() )
        {
            sleep( 10 );
            std::cout << "while";
            messageReceived = service.receive(1000); // Receive a message
            sleep(1000);
            std::cout << "while2";
            for (int i = 0; i < 10/*primes.size()*/; i++)
                {
                    std::cout << "while";
                    std::cout << "i = " << i << " sending prime: " << primes[i] << std::endl;
                    char * message = nullptr;
                    sprintf(message, "prime!>%d", primes[i]);
                    std::cout << "test";
                    service.send(message);
                    std::cout << "test2";
                    sleep(100);
                }
            // if (strcmp(messageReceived.c_str(), "prime?") == 0)
            // {
            //     sleep(100);
            //     std::cout << "sending primes...\n";
            //     service.send("prime!>");
            //     std::cout << "debug";
            //     for (int i = 0; i < 10/*primes.size()*/; i++)
            //     {
            //         std::cout << "i = " << i << " sending prime: " << primes[i] << std::endl;
            //         char * message = nullptr;
            //         sprintf(message, "prime!>%d", primes[i]);
            //         service.send(message);
            //         sleep(100);
            //     }
            // }
            // else
            // {
            //     std::cout << "waiting for message...\n";
            //     //service.send("prime!>no");
            // }
        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

    return 0;
}
