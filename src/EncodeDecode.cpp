//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include "../include/EncodeDecode.h"
#include <boost/lexical_cast.hpp>

std::string EncodeDecode::Decode(char msg[]){

    std::string result = "";
    short opcode = bytesToShort(msg, 0); // is this the correct way to extract???
    //std::cout<<"op " + std::to_string(opcode)<<std::endl;
    short msgOpcode = bytesToShort(msg, 2);
    //std::cout<<"msg op " + std::to_string(msgOpcode)<<std::endl;
    if(opcode == short(12)) {//ACK
        //std::cout<<"DECODEEE ACK"<<std::endl;
        result = "ACK " + std::to_string(msgOpcode) + " ";
        int index = 4;
        /*for(int i = 0 ; i <){
            result.append(1, msg[index]);
            index = index + 1;
        }*/
        while(msg[index] != '\0'){
            result.append(1, msg[index]);
            index = index + 1;
        }
    }
    else if(opcode == short(13)){
        result = "ERROR " + std::to_string(msgOpcode);
    }
    //std::cout<<result + "RESSS"<<std::endl;
    return result;
}

// decode
short EncodeDecode:: bytesToShort(char *msg, int i) {
    short result = (short)((msg[i] & 0xff) << 8);
    /*std::cout<<"bytes to short"<<std::endl;

    //std::cout<<result <<std::endl;
    std::string s = "";
    //std::cout<<s.append(1, msg[i])<<std::endl;
    //std::cout<<s.append(1, msg[i+1])<<std::endl;*/
    result += (short)(msg[i+1] & 0xff);
    return result;
}




std::string EncodeDecode:: Encode(std::string line){
// supposed to have string and turn into message??
    std::string enc = "";
    short op;
    int currIndex = line.find(" ");
    //std::cout<<currIndex<<std::endl;
    std::string opcode = line.substr(0, currIndex );
    //std::cout<<opcode<<std::endl;
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
                //std::cout<<"byte: "+ num[0]<<std::endl;
                //std::cout<<"byte: "+ num[1]<<std::endl;
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
    /*if(op == 4 || op == 8) {
        msg.append(1, '\0');
    }*/
    //std::cout<<msg<<std::endl;
    //std::cout<<msg + " GRRR"<<std::endl;
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