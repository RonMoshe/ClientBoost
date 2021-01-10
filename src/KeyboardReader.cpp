//
// Created by spl211 on 10/01/2021.
//

#include <string>
#include <iostream>
#include "../include/KeyboardReader.h"
#include "../include/MessageQueue.h"

KeyboardReader::KeyboardReader(std::mutex &mutex, MessageQueue &messageQueue1): mtx(mutex),
messageQueue(messageQueue1){}

void KeyboardReader::run() {
    while(true) {
        const short bufsize = 1024;
        char *buf = new char[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        //if(line.find("LOGOUT") != std::string::npos)
        //std::cout<<line<<std::endl;
        messageQueue.Enqueue(line);
        if(line.find("LOGOUT") != std::string::npos) {
            mtx.lock();
            if(messageQueue.shouldTerminate()) {
                std::cout<<"keyboard terminate"<<std::endl;
                break;
            }
        }

    }

}
