//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include "../include/Write.h"
#include "../include/ConnectionHandler.h"
#include "../include/EncodeDecode.h"

Write:: Write(ConnectionHandler &connectionHandler):connection(connectionHandler)
{
    //shouldTerminate = false;
}

//void Write::setShouldTerminate() {shouldTerminate = true;}

void Write :: operator()() {
    EncodeDecode * ed = new EncodeDecode ();
    while (true) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);

        //std::vector<string>;

        std::string line(buf);


        std::string encdec = ed->Encode(line);
        int len = encdec.length();

        if (!connection.sendLine(encdec)) { // encode first???
            std::cout << "Disconnected. Exiting...Write\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len + 1 << " bytes to serve r" << std::endl;
    }
}