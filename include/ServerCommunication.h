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
    ServerCommunication(ConnectionHandler &connectionHandler);

    void operator()(MessageQueue msgQueue);
private:
    ConnectionHandler connectionHandler;

    //EncodeDecode encdec;
};


#endif //CLIENT_SERVERCOMMUNICATION_H
