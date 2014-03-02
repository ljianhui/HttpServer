#include "tcpsocket.h"

TcpSocket::TcpSocket(Object *parent):
    Socket(AF_INET, SOCK_STREAM, 0, parent)
{
    ;
}

TcpSocket::TcpSocket(int protocotol, Object *parent):
    Socket(AF_INET, SOCK_STREAM, protocotol, parent)
{
    ;
}

TcpSocket::TcpSocket(const TcpSocket &tcp):
    Socket(tcp)
{
    ;
}

TcpSocket& TcpSocket::operator=(const TcpSocket &tcp)
{
    if(this != &tcp)
        Socket::operator=(tcp);
    return *this;
}
