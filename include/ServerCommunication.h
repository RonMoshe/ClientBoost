//
// Created by spl211 on 10/01/2021.
//

#ifndef CLIENT_SERVERCOMMUNICATION_H
#define CLIENT_SERVERCOMMUNICATION_H


#include "ConnectionHandler.h"
#include "EncodeDecode.h"
#include "MessageQueue.h"

class ServerCommunication {
public:
    ServerCommunication(std::mutex &mutex, ConnectionHandler &connectionHandler,
    MessageQueue &messageQueue);

    void run();
private:
    ConnectionHandler &connectionHandler;

    std::mutex &mtx;

    MessageQueue &messageQueue;

    //EncodeDecode encdec;
};


#endif //CLIENT_SERVERCOMMUNICATION_H
