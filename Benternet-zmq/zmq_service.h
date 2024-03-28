#ifndef ZMQ_SERVICE_H
#define ZMQ_SERVICE_H

#pragma once
#include <zmq.hpp>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

class ZMQ_service {
private:
    zmq::context_t  context;
    zmq::socket_t   MQ_push_socket  = zmq::socket_t(context, ZMQ_PUSH);
    zmq::socket_t   MQ_pull_socket  = zmq::socket_t(context, ZMQ_PULL);
    zmq::socket_t   MQ_sub_socket   = zmq::socket_t(context, ZMQ_SUB);
    bool            IsSubscribed    = false;
    
public:

                ZMQ_service (const std::string& sendAddress, const std::string& receiveAddress);
    void        send        (const char* message);
    std::string receive     (int timeoutMs);
    void        Subscribe   (std::string topic);
    bool        connected   ();

};


#endif // ZMQ_SERVICE_H
