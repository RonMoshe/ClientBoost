//
// Created by spl211 on 03/01/2021.
//

#include <string>

#ifndef BOOST_ECHO_CLIENT_ENCODEDECODE_H
#define BOOST_ECHO_CLIENT_ENCODEDECODE_H


class EncodeDecode {

public:

    std::string Decode(char msg[]);

    char* Encode(std::string line);

    short bytesToShort(char *msg, int i);

    void shortToBytes(short num, char* bytesArr);
};


#endif //BOOST_ECHO_CLIENT_ENCODEDECODE_H



