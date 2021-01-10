cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.45.0 COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Client include/ConnectionHandler.h
            src/ConnectionHandler.cpp
            src/Client.cpp include/EncodeDecode.h src/EncodeDecode.cpp
            include/Read.h src/Read.cpp include/Write.h src/Write.cpp src/ServerCommunication.cpp include/ServerCommunication.h src/KeyboardReader.cpp include/KeyboardReader.h src/MessageQueue.cpp include/MessageQueue.h)
    target_link_libraries(Client $ {Boost_LIBRARIES})
endif()


