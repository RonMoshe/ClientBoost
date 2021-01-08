//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
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
    short op;
    int currIndex = line.find(" ");
    std::cout<<currIndex<<std::endl;
    std::string opcode = line.substr(0, currIndex );
    std::cout<<opcode<<std::endl;
    enc = line.substr(currIndex+1);

    if(opcode.compare("ADMINREG") == 0){
        op = 1;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("STUDENTREG") == 0){
        op = 2;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("LOGIN") == 0){
        op = 3;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("LOGOUT") == 0){
        op = 4;
    }
    else if(opcode.compare("COURSEREG") == 0){
        op = 5;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("KDAMCHECK") == 0){
        op = 6;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("COURSESTAT") == 0){
        op = 7;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("STUDENTSTAT") == 0){
        op = 8;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("ISREGISTERED") == 0){
        op = 9;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("UNREGISTER") == 0){
        op = 10;
        //enc = line.substr(currIndex+1);
    }
    else if(opcode.compare("MYCOURSES") == 0){
        op = 11;
    }


    char* opc = new char[2];
    shortToBytes(op, opc);

    std::string msg = "";
    //msg.push_back(opc[0]);
    //msg.push_back(opc[1]);
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
        msg = msg + enc.substr(0, index);
        msg.append(1, '\0');
        enc = enc.substr(index + 1);

    }
    /*std::cout<<msg<<std::endl;
    while(enc.length() > 1){
        int index = enc.find(" ");
        if(index == 0){
            msg = msg + enc;
            enc = "";
            std::cout<<"IF : " + msg<<std::endl;
        }
        else {
            msg = msg + enc.substr(0, index);

            std::cout<<"Else : " + msg<<std::endl;
            if(enc.length() > index + 2) {
                msg.append(1, '\0');
                enc = enc.substr(index + 1);
            }
            else{
                enc = "";
            }
        }
    }*/

    if(op == 4 || op == 8) {
        msg.append(1, '\0');
    }
    //msg.append(1, '\0');
    std::cout<<msg<<std::endl;
    std::cout<<msg + " GRRR"<<std::endl;
    return msg;
}

// encode
void EncodeDecode::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

