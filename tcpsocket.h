#ifndef TCPSOCKET_H_INCLUDED
#define TCPSOCKET_H_INCLUDED

#include "socket.h"
#include "object.h"

class TcpSocket: public Socket
{
    public:
        TcpSocket(Object *parent = NULL);
        TcpSocket(int protocol, Object *parent = NULL);
        ~TcpSocket(){}

    private:
        TcpSocket(const TcpSocket &tcpsocket);
        TcpSocket& operator=(const TcpSocket &tcpsocket);
};

#endif // TCPSOCKET_H_INCLUDED
