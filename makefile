CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lboost_thread -pthread


all: bin/cTrace


bin/cTrace: bin/Client.o bin/ConnectionHandler.o bin/EncodeDecode.o bin/KeyboardReader.o bin/ServerCommunication.o bin/MessageQueue.o
		g++ -Wall -Weffc++ -o bin/cTrace bin/Client.o bin/ConnectionHandler.o bin/EncodeDecode.o bin/KeyboardReader.o bin/ServerCommunication.o bin/MessageQueue.o $(LDFLAGS)

bin/Client.o: src/Client.cpp
		g++ $(CFLAGS) -o bin/Client.o src/Client.cpp $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
		g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp $(LDFLAGS)

bin/EncodeDecode.o: src/EncodeDecode.cpp
		g++ $(CFLAGS) -o bin/EncodeDecode.o src/EncodeDecode.cpp $(LDFLAGS)

bin/KeyboardReader.o: src/KeyboardReader.cpp
		g++ $(CFLAGS) -o bin/KeyboardReader.o src/KeyboardReader.cpp $(LDFLAGS)

bin/ServerCommunication.o: src/ServerCommunication.cpp
		g++ $(CFLAGS) -o bin/ServerCommunication.o src/ServerCommunication.cpp $(LDFLAGS)

bin/MessageQueue.o: src/MessageQueue.cpp
		g++ $(CFLAGS) -o bin/MessageQueue.o src/MessageQueue.cpp $(LDFLAGS)

clean:
		rm -f bin/*
