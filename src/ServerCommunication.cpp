//
// Created by spl211 on 10/01/2021.
//

#include "../include/ServerCommunication.h"

ServerCommunication::ServerCommunication(std::mutex &mutex, ConnectionHandler &connectionHandler1,
MessageQueue &messageQueue1):
mtx(mutex), connectionHandler(connectionHandler1), messageQueue(messageQueue1){}

void ServerCommunication::run() {
    EncodeDecode *encdec = new EncodeDecode();
    while (true) {
        if(!messageQueue.isEmpty()) {
            std::string line = messageQueue.Dequeue();
            std::string encoded = encdec->Encode(line);
            //std::cout<<"after"<<std::endl;
            //std::cout << encoded << std::endl;
            if (!connectionHandler.sendLine((std::string &) encoded)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
            std::cout << "Sent " << encoded.length() << " bytes to server" << std::endl;

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

            std::string out = encdec->Decode(ans);
            std::cout << "REPLY: " + out << std::endl << std::endl;
            if (out.find("ACK 4") != std::string::npos) { // logout
                std::cout << "Exiting...Read\n" << std::endl;

                break;
            }
        }
    }

}
