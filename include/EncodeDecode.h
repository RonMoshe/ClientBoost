//
// Created by spl211 on 03/01/2021.
//

#include <string>

#ifndef BOOST_ECHO_CLIENT_ENCODEDECODE_H
#define BOOST_ECHO_CLIENT_ENCODEDECODE_H


class EncodeDecode {

public:

    std::string Decode(char msg[]);

    std::string Encode(std::string line);

    short bytesToShort(char *msg, int i);

    void shortToBytes(short num, char* bytesArr);

    bool from_string(short &sh, const std::string &str, std::ios_base& (*f)(std::ios_base&) = std::dec);
};


#endif //BOOST_ECHO_CLIENT_ENCODEDECODE_H



