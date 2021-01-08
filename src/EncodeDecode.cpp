//
// Created by spl211 on 03/01/2021.
//

#include "../include/EncodeDecode.h"

//short bytesToShort(char *msg, int i);

std::string EncodeDecode::Decode(char msg[]){
    std::string result = "";
    short opcode = bytesToShort(msg, 0); // is this the correct way to extract???
    short msgOpcode = bytesToShort(msg, 2);
    if(opcode == 12) {//ACK
        result = "ACK " + std::to_string(msgOpcode) + " ";
        int i = 4;
        while(!(msg[i] == '0')) {
            result += std::to_string(bytesToShort(msg, i));
            i=i+2;
        }
    }
    else if(opcode == 12){
        result = "ERROR " + msgOpcode;
    }
    return result;
}

// decode
short EncodeDecode:: bytesToShort(char *msg, int i) {
    short result = (short)((msg[i] & 0xff) << 8);
    result += (short)(msg[i+1] & 0xff);
    return result;
}




char* EncodeDecode:: Encode(std::string line){
// supposed to have string and turn into message??
    std::string enc = "";
    short op;
    int currIndex = line.find(" ");
    std::string opcode = line.substr(0, currIndex );
    if(opcode.compare("ADMINREG") == 0){
        op = 1;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("STUDENTREG") == 0){
        op = 2;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("LOGIN") == 0){
        op = 3;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("LOGOUT") == 0){
        op = 4;
    }
    else if(opcode.compare("COURSEREG") == 0){
        op = 5;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("KDAMCHECK") == 0){
        op = 6;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("COURSESTAT") == 0){
        op = 7;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("STUDENTSTAT") == 0){
        op = 8;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("ISREGISTERED") == 0){
        op = 9;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("UNREGISTER") == 0){
        op = 10;
        enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("MYCOURSES") == 0){
        op = 11;
    }
    int count;
    if(op == 1 || op == 2 || op == 3)
        count = 2;
    else if(op == 4 || op == 11)
        count = 0;
    else
        count = 1;
    char* msg = new char[enc.length()+ count +1];
    shortToBytes(op, msg);
    if(op != 4 && op != 8) {
        msg[2] = '\0';
        enc.replace(enc.begin(), enc.end(), ' ', '\0');
        for (int i = 0; i < enc.length(); i++) {
            msg[i + 3] = enc[i];
        }
    }
    msg[enc.length() + count] = '\0';
    return msg;
}

// encode
void EncodeDecode::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

