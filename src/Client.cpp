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
#include "../include/EncodeDecode.h"

//int main (int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//        return -1;
//    }
//
//    std::string host = argv[1];
//    short port = atoi(argv[2]);
//
//    ConnectionHandler connectionHandler(host, port);
//    if (!connectionHandler.connect()) {
//        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
//        return 1;
//    }
//    //std::this_thread::sleep_for(std::chrono::seconds (5));
//
//    // We can use one of three options to read data from the server:
//    // 1. Read a fixed number of characters
//    // 2. Read a line (up to the newline character using the getline() buffered reader
//    // 3. Read up to the null character
//
//    Read taskRead(connectionHandler);
//    Write taskWrite(connectionHandler);
//
//    std::thread taskThread1(&Read::operator(), taskRead);//taskRead.operator()()
//    std::thread taskThread2(&Write::operator(), taskWrite); //taskWrite.operator()(),
//
//    taskThread1.join();
//    taskThread2.detach();
//    // waits for read to end - successful logout
//    //std::string input;
//    //std::getline(std::cin, input);
//    //taskWrite.setShouldTerminate(); // once we logout we want to disconnect
//    // disconnecting
//    //taskThread2.detach();//???
//    std::cout << "Disconnected. Exiting...Main\n" << std::endl;
//    //std::terminate();
//}


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

    //From here we will see the rest of the ehco client implementation:
    EncodeDecode * ed = new EncodeDecode ();

    while (1) {
        const short bufsize = 1024;
        char *buf = new char[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len=line.length();
        std::cout<<"before"<<std::endl;
        std::string encoded = ed->Encode(line);
        std::cout<<"after"<<std::endl;
        std::string s = "02ron";
        std::string str = s.append(1, '\0') + "moshe" ;
        str.append(1, '\0');
        std::cout << encoded << std::endl;
        if (!connectionHandler.sendLine((std::string &) encoded)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << encoded.length() << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        std::cout << "Before read from server...\n" << std::endl;

        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        std::string Answer;

        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine((std::string &)Answer)) {
            std::cout << "Disconnected. Exiting...Read\n" << std::endl;
            break;
        }
        std::cout <<"After read from server"  << std::endl;
        std::cout <<Answer  << std::endl;
        std::cout <<"After print Answer"  << std::endl;
        char ans [Answer.length()];
        //strcpy(ans, Answer.c_str());
        for(int i = 0; i < Answer.length(); i++){
            ans[i] = Answer[i];
        }

        //int len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        //ans->
        EncodeDecode * ed = new EncodeDecode ();
        std::string out = ed->Decode(ans);
        std::cout <<"REPLY: " + out   << std::endl << std::endl;
        if (out.find("04")!=std::string::npos && out.find("ACK")!=std::string::npos) { // logout
            std::cout << "Exiting...Read\n" << std::endl;

            break;
        }

        /*if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len-1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }*/
    }
    return 0;
}





