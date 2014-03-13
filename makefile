all: MyHttpServer

# Which compiler
CC=g++

#Compile options
COPTIONS=-lpthread

#Include
INCLUED =

#Objfiles
OBJFILE=main.o object.o mutex.o socket.o thread.o tcpsocket.o httpheader.o httprequestheader.o http.o logfile.o commonfunction.o httpkeyvalue.o httpresponseheader.o httpserver.o

MyHttpServer: $(OBJFILE) 
	$(CC) -o MyHttpServer $(OBJFILE) $(COPTIONS) 

main.o: main.cpp httpserver.h
	$(CC) -c main.cpp $(COPTIONS)

commonfunction.o: commonfunction.h commonfunction.cpp
	$(CC) -c commonfunction.cpp

logfile.o: logfile.h logfile.cpp object.h
	$(CC) -c logfile.cpp

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

httpresponseheader.o: httpresponseheader.h httpresponseheader.cpp httpheader.h
	$(CC) -c httpresponseheader.cpp

http.o: http.cpp http.h object.h tcpsocket.h httprequestheader.h httpresponseheader.h
	$(CC) -c http.cpp

httpkeyvalue.o: httpkeyvalue.h httpkeyvalue.cpp mutex.h
	$(CC) -c httpkeyvalue.cpp $(COPTIONS)

httpserver.o: httpserver.h httpserver.cpp tcpsocket.h http.h httprequestheader.h httpresponseheader.h
	$(CC) -c httpserver.cpp $(COPTIONS)
clean:
	-rm -f *.o
