#include "zmq_service.h"

#pragma once
#include <iostream>
#include <zmq.hpp>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif


ZMQ_service::ZMQ_service(const std::string& sendAddress, const std::string& receiveAddress) {
    MQ_push_socket.connect(sendAddress);
    MQ_pull_socket.connect(receiveAddress); // Connect the pull socket to the same address as the push socket
}

void ZMQ_service::send(const char* message) {
    int length = strlen(message);
    MQ_push_socket.send(message, length);
    std::cout << "Pushed : [" << message << "]" << std::endl;
}


std::string ZMQ_service::receive(int timeoutMs) {
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

bool ZMQ_service::connected() {
    return MQ_push_socket.connected() && MQ_pull_socket.connected();
}