#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "object.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct sockaddr sockaddr;

class Socket: public Object
{
    public:
        Socket(Object *parent = NULL);
        Socket(int domain, int type, int protocol = 0,
               Object *parent = NULL);
        Socket(const Socket &socket);
        Socket& operator=(const Socket &socket);
        virtual ~Socket();

        void initSocket(int domain, int type, int protocol = 0);
        int bind();
        int listen(int backlog);
        int accept(Socket &acc_sock);
        int connectToHost();
        int closeSocket();

        void setSocketAddress(short int family, unsigned short int port,
                              const char *hostname);
        void setSocketAddress(short int family, unsigned short int port,
                              unsigned long int address);

        inline int sendData(const char *data, int data_size);
        inline int receiveData(char *buffer, int buff_size);

        inline int getLocalSocket()const;
        inline int getPeerSocket()const;
        inline short int getLocalPort()const;
        inline short int getPeerPort()const;

        inline const sockaddr* getPeerAddress()const;
        inline const sockaddr* getLocalAddress()const;

    private:
        void _assign(const Socket &socket);

        int local_sockfd;
        struct sockaddr_in local_addr;

        int peer_sockfd;
        struct sockaddr_in peer_addr;
};

int Socket::sendData(const char *data, int data_size)
{
    return write(peer_sockfd, data, data_size);
}

int Socket::receiveData(char *buffer, int buff_size)
{
    return read(peer_sockfd, buffer, buff_size);
}

int Socket::getLocalSocket()const
{
    return local_sockfd;
}

int Socket::getPeerSocket()const
{
    return peer_sockfd;
}

short int Socket::getLocalPort()const
{
    return ntohs(local_addr.sin_port);
}

short int Socket::getPeerPort()const
{
    return ntohs(peer_addr.sin_port);
}

const sockaddr* Socket::getLocalAddress()const
{
    return (const sockaddr*)&local_addr;
}

const sockaddr* Socket::getPeerAddress()const
{
    return (const sockaddr*)&peer_addr;
}

#endif // SOCKET_H_INCLUDED
