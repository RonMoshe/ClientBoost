//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include "../include/Write.h"
#include "../include/ConnectionHandler.h"
#include "../include/EncodeDecode.h"
#include <mutex>

Write::Write(){}
/*Write:: Write(ConnectionHandler &connectionHandler):connection(connectionHandler)
{
    //shouldTerminate = false;
}*/

//void Write::setShouldTerminate() {shouldTerminate = true;}

void Write :: operator()(ConnectionHandler &connection) {
    std::mutex mtx;
    EncodeDecode * ed = new EncodeDecode ();
    bool shouldTerminate = false;
    while (!shouldTerminate) {
        const short bufsize = 1024;
        char *buf = new char[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);

        std::cout<<"before"<<std::endl;
        std::string encoded = ed->Encode(line);
        std::cout<<"after"<<std::endl;
        std::cout << encoded << std::endl;
        if (!connection.sendLine((std::string &) encoded)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        /*const short bufsize = 1024;
        char* buf = new char[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);

        std::string encdec = ed->Encode(line);
        std::cout<<encdec<<std::endl;


        if (!connection.sendLine((std::string &)encdec)) { // encode first???
            std::cout << "Disconnected. Exiting...Write\n" << std::endl;
            break;
        }*/
        if(line.find("LOGOUT")!=std::string::npos){
            mtx.lock();
            shouldTerminate = connection.getShouldTerminate();
        }

    }
}