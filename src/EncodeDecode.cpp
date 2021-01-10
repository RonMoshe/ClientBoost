//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include "../include/EncodeDecode.h"
#include <boost/lexical_cast.hpp>

std::string EncodeDecode::Decode(char msg[]){

    std::string result = "";
    short opcode = bytesToShort(msg, 0); // is this the correct way to extract???
    short msgOpcode = bytesToShort(msg, 2);
    if(opcode == short(12)) {//ACK
        result = "ACK " + std::to_string(msgOpcode);
        int index = 4;
        if(msg[index] != '\0'){
            result.append(1, '\n');
        }
        while(msg[index] != '\0'){
            result.append(1, msg[index]);
            index = index + 1;
        }
    }
    else if(opcode == short(13)){
        result = "ERROR " + std::to_string(msgOpcode);
    }
    return result;
}

// decode
short EncodeDecode:: bytesToShort(char *msg, int i) {
    short result = (short)((msg[i] & 0xff) << 8);
    result += (short)(msg[i+1] & 0xff);
    return result;
}




std::string EncodeDecode:: Encode(std::string line){
// supposed to have string and turn into message??
    std::string enc = "";
    short op;
    int currIndex = line.find(" ");
    std::string opcode = line.substr(0, currIndex );
    enc = line.substr(currIndex+1);

    if(opcode.compare("ADMINREG") == 0){
        op = 1;
    }
    else if(opcode.compare("STUDENTREG") == 0){
        op = 2;
    }
    else if(opcode.compare("LOGIN") == 0){
        op = 3;
    }
    else if(opcode.compare("LOGOUT") == 0){
        op = 4;
    }
    else if(opcode.compare("COURSEREG") == 0){
        op = 5;
    }
    else if(opcode.compare("KDAMCHECK") == 0){
        op = 6;
    }
    else if(opcode.compare("COURSESTAT") == 0){
        op = 7;
    }
    else if(opcode.compare("STUDENTSTAT") == 0){
        op = 8;
    }
    else if(opcode.compare("ISREGISTERED") == 0){
        op = 9;
    }
    else if(opcode.compare("UNREGISTER") == 0){
        op = 10;
    }
    else if(opcode.compare("MYCOURSES") == 0){
        op = 11;
    }
    char* opc = new char[2];
    shortToBytes(op, opc);
    std::string msg = "";
    msg.append(1, opc[0]);
    msg.append(1, opc[1]);
    int count;
    if(op == 1 || op == 2 || op == 3)
        count = 2;
    else if(op == 4 || op == 11)
        count = 0;
    else
        count = 1;
    for(int i = 0; i < count; i++){
        int index = enc.find(" ");
        std::string s = enc.substr(0, index);
        if(op == 5 || op == 6 || op == 7 || op == 9 || op == 10){
            short shor;
            if(from_string(shor, s)){
                char* num = new char[2];
                shortToBytes(shor, num);
                msg.append(1, num[0]);
                msg.append(1, num[1]);
            }

        }
        else {
            msg = msg + s;
            msg.append(1, '\0');
        }

        enc = enc.substr(index + 1);
    }
    return msg;
}

// encode
void EncodeDecode::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

// turn string into short
bool EncodeDecode::from_string(short &sh, const std::string &str, std::ios_base& (*f)(std::ios_base&) /*= std::dec*/){
    std::istringstream iss(str);
    return !(iss>>f>>sh).fail();
}