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

        inline int sendData(const char *data, int data_size)const;
        inline int receiveData(char *buffer, int buff_size)const;

        inline short int getLocalPort();
        inline short int getPeerPort();

        const sockaddr* getPeerAddress(int *len = NULL);
        const sockaddr* getLocalAddress(int *len = NULL);

    private:
        Socket(const Socket &socket);
        Socket& operator=(const Socket &socket);
        void _assign(const Socket &socket);

        int local_sockfd;
        struct sockaddr_in address;
};

int Socket::sendData(const char *data, int data_size)const
{
    return write(local_sockfd, data, data_size);
}

int Socket::receiveData(char *buffer, int buff_size)const
{
    return read(local_sockfd, buffer, buff_size);
}

short int Socket::getLocalPort()
{
    socklen_t addr_len = sizeof(address);
    int res = getsockname(local_sockfd, (sockaddr*)&address, &addr_len);
    if(res == 0)
        return ntohs(address.sin_port);
    return -1;
}

short int Socket::getPeerPort()
{
    socklen_t addr_len = sizeof(address);
    int res = getpeername(local_sockfd, (sockaddr*)&address, &addr_len);
    if(res == 0)
        return ntohs(address.sin_port);
    return -1;
}


#endif // SOCKET_H_INCLUDED
