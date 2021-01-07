//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include <thread>
#include "../include/ConnectionHandler.h"
#include "../include/Read.h"
#include "../include/Write.h"
#include <pthread.h>





//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include <thread>
#include "../include/ConnectionHandler.h"
#include "../include/Read.h"
#include "../include/Write.h"

int main (int argc, char *argv[]) {
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
    //std::this_thread::sleep_for(std::chrono::seconds (5));

    // We can use one of three options to read data from the server:
    // 1. Read a fixed number of characters
    // 2. Read a line (up to the newline character using the getline() buffered reader
    // 3. Read up to the null character

    Read taskRead(connectionHandler);
    Write taskWrite(connectionHandler);

    std::thread taskThread1(&Read::operator(), taskRead);//taskRead.operator()()
    std::thread taskThread2(&Write::operator(), taskWrite); //taskWrite.operator()(),

    taskThread1.join();
    taskThread2.join();
    // waits for read to end - successful logout
    //std::string input;
    //std::getline(std::cin, input);
    //taskWrite.setShouldTerminate(); // once we logout we want to disconnect
    // disconnecting
    //taskThread2.detach();//???
    std::cout << "Disconnected. Exiting...Main\n" << std::endl;
    //std::terminate();
}





