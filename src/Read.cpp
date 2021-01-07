//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include "../include/Read.h"
#include "../include/ConnectionHandler.h"
#include "../include/EncodeDecode.h"

Read :: Read(ConnectionHandler &connectionHandler):
connection(connectionHandler){}

void Read:: operator()(){
    bool run = true;
    EncodeDecode * ed = new EncodeDecode ();
    while(run){
        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connection.getLine((std::string &) answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        char ans [answer.length()];
        strcpy(ans, answer.c_str());

        int len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        //ans->

        std::cout << ed->Decode(ans)  << std::endl << std::endl;
        if (answer.find("04")!=std::string::npos && answer.find("12")!=std::string::npos) { // logout
            std::cout << "Exiting...\n" << std::endl;
            run = false;
            break;
        }
    }
}
