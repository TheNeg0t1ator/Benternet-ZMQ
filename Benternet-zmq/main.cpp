#include <iostream>
#include <zmq.hpp>
#include "zmq_service.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

int main( void )
{
    try
    {
        ZMQ_service service("tcp://benternet.pxl-ea-ict.be:24041","tcp://benternet.pxl-ea-ict.be:24042" );
        //"tcp://192.168.1.8:24041"
        //"tcp://localhost:24041"
        //"tcp://benternet.pxl-ea-ict.be:24041"
        char * messagetosend = "prime?";
        if( service.connected() )
        {
            service.send(messagetosend);
            service.Subscribe("prime");
        }

        while( service.connected() )
        {
            sleep( 10 );
            service.receive(1000); // Receive a message
        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

    return 0;
}
