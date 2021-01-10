//
// Created by spl211 on 10/01/2021.
//

#ifndef CLIENT_SERVERCOMMUNICATION_H
#define CLIENT_SERVERCOMMUNICATION_H


#include "ConnectionHandler.h"
#include "EncodeDecode.h"

class ServerCommunication {
public:
    ServerCommunication(ConnectionHandler &connectionHandler, EncodeDecode &encodeDecode);

    void operator()();
private:
    ConnectionHandler connectionHandler;

    EncodeDecode encdec;
};


#endif //CLIENT_SERVERCOMMUNICATION_H
