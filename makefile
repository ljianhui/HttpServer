all: myhttp

# Which compiler
CC=g++

#Compile options
COPTIONS=-lpthread

#Include
INCLUED =

myhttp: main.o object.o mutex.o socket.o thread.o tcpsocket.o httpheader.o httprequestheader.o http.o
	$(CC) -o myhttp main.o object.o  mutex.o socket.o thread.o tcpsocket.o httpheader.o httprequestheader.o http.o  $(COPTIONS)

main.o: main.cpp object.h mutex.h socket.h thread.h tcpsocket.h
	$(CC) -c main.cpp $(COPTIONS)

object.o: object.cpp object.h
	$(CC) -c object.cpp    

mutex.o: mutex.cpp mutex.h object.h
	$(CC) -c mutex.cpp $(COPTIONS)

thread.o: thread.cpp thread.h object.h
	$(CC) -c thread.cpp $(COPTIONS)

socket.o: socket.cpp socket.h object.h
	$(CC) -c socket.cpp

tcpsocket.o: tcpsocket.cpp tcpsocket.h socket.h
	$(CC) -c tcpsocket.cpp

httpheader.o: httpheader.cpp httpheader.h object.h
	$(CC) -c httpheader.cpp

httprequestheader.o: httprequestheader.cpp httprequestheader.h httpheader.h
	$(CC) -c httprequestheader.cpp

http.o: http.cpp http.h object.h tcpsocket.h httprequestheader.h httpresponseheader.h
	$(CC) -c http.cpp
clean:
	-rm -f *.o
