//
// Created by spl211 on 10/01/2021.
//

#include <iostream>
#include "../include/MessageQueue.h"
#include "mutex"

MessageQueue::MessageQueue(): messageQueue(), mtx(){}

void MessageQueue::Enqueue(std::string msg){
    messageQueue.push_back(msg);
    //std::cout<<"Added to queue"<<std::endl;
}

std::string MessageQueue::Dequeue() {
    mtx.lock();
    std::string msg = messageQueue.front();
    messageQueue.erase(messageQueue.begin());
    mtx.unlock();
    return msg;
}

bool MessageQueue::isEmpty() {
    return messageQueue.size() == 0;
}
