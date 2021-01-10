//
// Created by spl211 on 10/01/2021.
//

#ifndef CLIENT_MESSAGEQUEUE_H
#define CLIENT_MESSAGEQUEUE_H


#include <vector>
#include <string>

class MessageQueue {
public:
    void Push(std::string msg);

    std::string Pop();

    bool isEmpty();

private:
    std::vector<std::string> MessageQueue;

};


#endif //CLIENT_MESSAGEQUEUE_H
