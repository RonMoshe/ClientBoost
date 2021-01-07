//
// Created by spl211 on 03/01/2021.
//

#ifndef BOOST_ECHO_CLIENT_READ_H
#define BOOST_ECHO_CLIENT_READ_H


#include "ConnectionHandler.h"

class Read {
public:
    Read(ConnectionHandler &connectionHandler);
    void operator()();

private:
    ConnectionHandler connection;
};




#endif //BOOST_ECHO_CLIENT1_READ_H
