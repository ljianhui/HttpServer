#include "httpserver.h"

int main(int argc, char **argv)
{
    HttpServer server;
    if(argc > 1)
        server.setRootDir(argv[1]);
    if(argc > 2)
        server.setLogFileName(argv[2]);

    server.setSocketAddress(AF_INET, (unsigned long int)INADDR_ANY, (unsigned short int)80);
    server.bind();
    server.listen(10);
    while(true)
    {
        TcpSocket *tcp = new TcpSocket;
        server.accept(*tcp);
        server.createServer((void*)tcp);
    }
}
