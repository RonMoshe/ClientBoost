CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lboost_thread -pthread


all: bin/cTrace


bin/cTrace: bin/Client.o bin/ConnectionHandler.o bin/EncodeDecode.o bin/Read.o bin/Write.o
		g++ -Wall -Weffc++ -o bin/cTrace bin/Client.o bin/ConnectionHandler.o bin/EncodeDecode.o bin/Read.o bin/Write.o $(LDFLAGS)

bin/Client.o: src/Client.cpp
		g++ $(CFLAGS) -o bin/Client.o src/Client.cpp $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
		g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp $(LDFLAGS)

bin/EncodeDecode.o: src/EncodeDecode.cpp
		g++ $(CFLAGS) -o bin/EncodeDecode.o src/EncodeDecode.cpp $(LDFLAGS)

bin/Read.o: src/Read.cpp
		g++ $(CFLAGS) -o bin/Read.o src/Read.cpp $(LDFLAGS)

bin/Write.o: src/Write.cpp
		g++ $(CFLAGS) -o bin/Write.o src/Write.cpp $(LDFLAGS)

clean:
		rm -f bin/*
