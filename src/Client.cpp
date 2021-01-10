//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include <thread>
#include "../include/ConnectionHandler.h"
#include <pthread.h>





//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include <thread>
#include <queue>

#include "../include/EncodeDecode.h"
#include "../include/MessageQueue.h"
#include "../include/KeyboardReader.h"
#include "../include/ServerCommunication.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    std::mutex mtx;
    MessageQueue msgQueue;
    KeyboardReader keyboardReader((std::mutex &)mtx, (MessageQueue &) msgQueue);
    ServerCommunication srvrC((std::mutex &) mtx, (ConnectionHandler &) connectionHandler, (MessageQueue &)msgQueue);
    std::thread taskKeyboard(&KeyboardReader::run, &keyboardReader);
    std::thread taskServerC(&ServerCommunication::run, &srvrC);
    taskServerC.join();
    taskKeyboard.detach();
    std::cout<<"Exiting...Finished program"<<std::endl;
}





