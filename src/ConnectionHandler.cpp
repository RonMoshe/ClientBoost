//
// Created by spl211 on 03/01/2021.
//

#include "../include/ConnectionHandler.h"

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

ConnectionHandler::ConnectionHandler(string host, short port): host_(host), port_(port), io_service_(), socket_(io_service_){}

ConnectionHandler::~ConnectionHandler() {
    close();
}

bool ConnectionHandler::connect() {
    std::cout << "Starting connect to "
              << host_ << ":" << port_ << std::endl;
    try {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
        boost::system::error_code error;
        socket_.connect(endpoint, error);
        if (error) {
            throw boost::system::system_error(error);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
            tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        //std::cerr << "recv failed0 from server(Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed1 to server(Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\0');
}

bool ConnectionHandler::sendLine(std::string& line) {
    return sendFrameAscii(line, '\0');
}


bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char ch;
    // Stop when we encounter the null character.
    // Notice that the null character is not appended to the frame string.
    try {
        int i = 0;
        do{
            if(!getBytes(&ch, 1))
            {
                return false;
            }
            if(ch!='\0' || i < 3) {
                frame.append(1, ch);
            }
            i = i + 1;
            if(i == 4){
                if(((short)(frame[1] & 0xff)) == ((short)13)){
                    return true;
                }
            }
        }while (delimiter != ch || i < 4);
    } catch (std::exception& e) {
        std::cerr << "recv failed2 Get from server (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    frame.append(1, '\0');
    return true;
}


bool ConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
    bool result=sendBytes(frame.c_str(),frame.length());
    if(!result) {
        std::cout<<"not sent"<<std::endl;
        return false;
    }
    return result;
}

// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}

ConnectionHandler::ConnectionHandler(ConnectionHandler const &handler):host_(handler.host_),
         port_(handler.port_), io_service_(), socket_(io_service_){}
