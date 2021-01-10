//
// Created by spl211 on 10/01/2021.
//

#include <string>
#include <iostream>
#include "../include/KeyboardReader.h"
#include "../include/MessageQueue.h"

void KeyboardReader::operator()(MessageQueue msgQueue) {
    while(true) {
        const short bufsize = 1024;
        char *buf = new char[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        //if(line.find("LOGOUT") != std::string::npos)
        msgQueue.Enqueue(line);
    }
}
