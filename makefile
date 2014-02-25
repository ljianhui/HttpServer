all: myhttp

# Which compiler
CC=g++

#Compile options
COPTIONS=-lpthread

#Include
INCLUED =

myhttp: main.o object.o mutex.o socket.o thread.o tcpsocket.o
	$(CC) -o myhttp main.o object.o  mutex.o socket.o thread.o tcpsocket.o $(COPTIONS)

main.o: main.cpp object.h mutex.h socket.h thread.h tcpsocket.h
	$(CC) -c main.cpp $(COPTIONS)

object.o: object.cpp object.h
	$(CC) -c object.cpp $(COPTIONS)    

mutex.o: mutex.cpp mutex.h object.h
	$(CC) -c mutex.cpp $(COPTIONS)

thread.o: thread.cpp thread.h object.h
	$(CC) -c thread.cpp $(COPTIONS)

socket.o: socket.cpp socket.h object.h
	$(CC) -c socket.cpp $(COPTIONS)

tcpsocket.o: tcpsocket.cpp tcpsocket.h socket.h
	$(CC) -c tcpsocket.cpp $(COPTIONS)


clean:
	-rm -f main.o object.o mutex.o thread.o socket.o tcpsocket.o
