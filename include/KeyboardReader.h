//
// Created by spl211 on 10/01/2021.
//

#ifndef CLIENT_KEYBOARDREADER_H
#define CLIENT_KEYBOARDREADER_H


#include "MessageQueue.h"

class KeyboardReader {
public:
    KeyboardReader(std::mutex &mutex, MessageQueue &messageQueue);
    void run();
private:
    std::mutex &mtx;

    MessageQueue &messageQueue;

};


#endif //CLIENT_KEYBOARDREADER_H
