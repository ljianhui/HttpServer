#include "httpserver.h"

int main()
{
    HttpServer server;
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
