//
// Created by spl211 on 03/01/2021.
//

#ifndef BOOST_ECHO_CLIENT1_WRITE_H
#define BOOST_ECHO_CLIENT1_WRITE_H


#include "ConnectionHandler.h"

class Write {
public:
    Write(ConnectionHandler &connectionHandler);

    void operator()();

    //void setShouldTerminate();

private:
    ConnectionHandler connection;

    //std::atomic_bool shouldTerminate;

};


#endif //BOOST_ECHO_CLIENT1_WRITE_H
