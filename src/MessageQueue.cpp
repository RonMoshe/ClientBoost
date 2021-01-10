//
// Created by spl211 on 10/01/2021.
//

#include "../include/MessageQueue.h"

MessageQueue::MessageQueue(): messageQueue(){}

void MessageQueue::Enqueue(std::string msg){
    messageQueue.push_back(msg);
}

std::string MessageQueue::Dequeue() {
    std::string msg = messageQueue.front();
    messageQueue.erase(messageQueue.begin());
    return msg;
}

bool MessageQueue::isEmpty() {
    return messageQueue.size() == 0;
}
