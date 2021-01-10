//
// Created by spl211 on 10/01/2021.
//

#ifndef CLIENT_KEYBOARDREADER_H
#define CLIENT_KEYBOARDREADER_H


#include "MessageQueue.h"

class KeyboardReader {
public:
    void operator()(MessageQueue msgQueue);

};


#endif //CLIENT_KEYBOARDREADER_H
