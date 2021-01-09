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
    EncodeDecode * ed = new EncodeDecode ();
    while(true){
        //std::cout<<"start read run "<<std::endl;
        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;

        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if(!connection.getLine((std::string &) answer)) {
            std::cout << "Disconnected. Exiting...Read\n" << std::endl;
            break;
        }

        char ans[answer.length()];
        for(int i = 0; i < answer.length(); i++){
            ans[i] = answer[i];
        }

        //int len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        //ans->
        std::string out = ed->Decode(ans);
        std::cout << out  << std::endl << std::endl;
        if (out.find("04")!=std::string::npos && out.find("ACK")!=std::string::npos) { // logout
            std::cout << "Exiting...Read\n" << std::endl;
            break;
        }
    }
}
