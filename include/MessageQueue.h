//
// Created by spl211 on 10/01/2021.
//

#ifndef CLIENT_MESSAGEQUEUE_H
#define CLIENT_MESSAGEQUEUE_H


#include <vector>
#include <string>
#include <mutex>

class MessageQueue {
public:
    void Enqueue(std::string msg);

    std::string Dequeue();

    bool isEmpty();

    MessageQueue();

private:
    std::vector<std::string> messageQueue;

    std::mutex mtx;

};


#endif //CLIENT_MESSAGEQUEUE_H