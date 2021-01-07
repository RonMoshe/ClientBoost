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



std::string EncodeDecode:: Encode(std::string line){
// supposed to have string and turn into message??
    std::string enc = "";
    int currIndex = line.find(" ");
    std::string opcode = line.substr(0, currIndex );
    if(opcode.compare("ADMINREG") == 0){
        enc = "1" + line.substr(currIndex+1);
    }
    if(opcode.compare("STUDENTREG") == 0){
        enc = "2" + line.substr(currIndex+1);
    }
    if(opcode.compare("LOGIN") == 0){
        enc = "3" + line.substr(currIndex+1);
    }
    if(opcode.compare("LOGOUT") == 0){
        enc = "4";
    }
    if(opcode.compare("COURSEREG") == 0){
        enc = "5" +line.substr(currIndex+1);
    }
    if(opcode.compare("KDAMCHECK") == 0){
        enc = "6" +line.substr(currIndex+1);
    }
    if(opcode.compare("COURSESTAT") == 0){
        enc = "7" +line.substr(currIndex+1);
    }
    if(opcode.compare("STUDENTSTAT") == 0){
        enc = "8" +line.substr(currIndex+1);
    }
    if(opcode.compare("ISREGISTERED") == 0){
        enc = "9" +line.substr(currIndex+1);
    }
    if(opcode.compare("UNREGISTER") == 0){
        enc = "10" +line.substr(currIndex+1);
    }
    if(opcode.compare("MYCOURSES") == 0){
        enc = "11";
    }
    return enc.replace(enc.begin(), enc.end(), ' ', '\0') + '\0';
}

// encode
void EncodeDecode::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

