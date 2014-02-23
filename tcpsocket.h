#ifndef TCPSOCKET_H_INCLUDED
#define TCPSOCKET_H_INCLUDED

#include "socket.h"

class TcpSocket: public Socket
{
    public:
        TcpSocket(Socket *parent = NULL);
        TcpSocket(int protocol, Socket *parent = NULL);
        TcpSocket(const TcpSocket &tcpsocket);
        TcpSocket& operator=(const TcpSocket &tcpsocket);
        ~TcpSocket(){}
};

#endif // TCPSOCKET_H_INCLUDED
