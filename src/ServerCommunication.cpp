//
// Created by spl211 on 10/01/2021.
//

#include "../include/ServerCommunication.h"

ServerCommunication::ServerCommunication(ConnectionHandler &connectionHandler1, EncodeDecode &encodeDecode):
connectionHandler(connectionHandler1), encdec(encodeDecode){}

void ServerCommunication::operator()() {
    while (true) {
        /*const short bufsize = 1024;
        char *buf = new char[bufsize];
        //std::cin.getline(buf, bufsize);
        std::string line(buf);*/

        //std::cout<<"before"<<std::endl;
        std::string encoded = encdec.Encode(line);
        //std::cout<<"after"<<std::endl;
        //std::cout << encoded << std::endl;
        if (!connectionHandler.sendLine((std::string &) encoded)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << encoded.length() << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        //std::cout << "Before read from server...\n" << std::endl;

        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        std::string Answer;

        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine((std::string &) Answer)) {
            std::cout << "Disconnected. Exiting...Read\n" << std::endl;
            break;
        }
        //std::cout <<"After read from server"  << std::endl;
        //std::cout <<Answer  << std::endl;
        //std::cout <<"After print Answer"  << std::endl;
        char ans[Answer.length()];
        //strcpy(ans, Answer.c_str());
        for (int i = 0; i < Answer.length(); i++) {
            ans[i] = Answer[i];
        }

        //int len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        //ans->

        std::string out = encdec.Decode(ans);
        std::cout << "REPLY: " + out << std::endl << std::endl;
        if (out.find("ACK 4") != std::string::npos) { // logout
            std::cout << "Exiting...Read\n" << std::endl;

            break;
        }
    }

}
