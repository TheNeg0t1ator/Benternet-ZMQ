#include <iostream>
#include <zmq.hpp>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

class ZMQ_service {
private:
    zmq::context_t context;
    zmq::socket_t MQ_push_socket = zmq::socket_t(context, ZMQ_PUSH);
    zmq::socket_t MQ_pull_socket = zmq::socket_t(context, ZMQ_PULL);
public:
    ZMQ_service(const std::string& sendAddress, const std::string& receiveAddress) {
        MQ_push_socket.connect(sendAddress);
        MQ_pull_socket.connect(receiveAddress); // Connect the pull socket to the same address as the push socket
    }

    void send(const char* message) {
        int length = strlen(message);
        MQ_push_socket.send(message, length);
        std::cout << "Pushed : [" << message << "]" << std::endl;
    }

    std::string receive(int timeoutMs) {
        zmq::message_t message;
        MQ_pull_socket.setsockopt(ZMQ_RCVTIMEO, &timeoutMs, sizeof(timeoutMs));
        try {
            MQ_pull_socket.recv(&message);
            std::string receivedMessage(static_cast<char*>(message.data()), message.size());
            std::cout << "Received : [" << receivedMessage << "]" << std::endl;
            return receivedMessage;
        } catch (zmq::error_t& ex) {
            if (ex.num() == EAGAIN) {
                std::cout << "Receive timeout" << std::endl;
            } else {
                throw ex;
            }
        }
        return "";
    }

    bool connected() {
        return MQ_push_socket.connected() && MQ_pull_socket.connected();
    }
};

int main( void )
{
    try
    {
        ZMQ_service service("tcp://benternet.pxl-ea-ict.be:24041","tcp://localhost:24041" );
        // ventilator.connect( "tcp://192.168.1.8:24041" );
        // ventilator.connect( "tcp://localhost:24041" );
        // ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        char * messagetosend = "example>quest?>barrie>";
        while( service.connected() )
        {
            sleep( 1000 );
            service.send(messagetosend);
            service.receive(1000); // Receive a message
        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }

    return 0;
}
