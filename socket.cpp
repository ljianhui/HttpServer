#include "socket.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

Socket::Socket(Object *parent):
    Object(parent),
    local_sockfd(-1)
{
    bzero(&address, sizeof(address));
}

Socket::Socket(int domain, int type, int protocol,
               Object *parent):
    Object(parent)
{
    local_sockfd = socket(domain, type, protocol);
    bzero(&address, sizeof(address));
}

Socket::Socket(const Socket &socket):
    Object(socket)
{
    _assign(socket);
}

Socket& Socket::operator=(const Socket &socket)
{
    if(this != &socket)
    {
        Object::operator=(socket);

        if(local_sockfd != -1)
            close(local_sockfd);
        _assign(socket);
    }
    return *this;
}

Socket::~Socket()
{
    if(local_sockfd != -1)
        close(local_sockfd);
}

void Socket::initSocket(int domain, int type, int protocol)
{
    if(local_sockfd != -1)
    {
        local_sockfd = socket(domain, type, protocol);
    }
}

int Socket::bind()
{
    return ::bind(local_sockfd,
                  (struct sockaddr*)&address,
                  sizeof(address));
}

int Socket::listen(int backlog)
{
    return ::listen(local_sockfd, backlog);
}

int Socket::accept(Socket &acc_sock)
{
    bzero(&acc_sock, sizeof(acc_sock));
    acc_sock.local_sockfd = -1;

    acc_sock.local_sockfd = ::accept(local_sockfd, NULL, NULL);
    return acc_sock.local_sockfd;
}

int Socket::connectToHost()
{
    int res = connect(local_sockfd,
                      (struct sockaddr*)&address,
                      sizeof(address));
    return res;
}

int Socket::closeSocket()
{
    int res = 0;
    if(local_sockfd != -1)
    {
        res = close(local_sockfd);
        local_sockfd = -1;
        return res;
    }
    return res;
}

void Socket::setSocketAddress(short int family, unsigned short int port,
                              const char *hostname)
{
    address.sin_family = family;
    address.sin_port = htons(port);
    inet_pton(family, hostname, &address.sin_addr);
}

void Socket::setSocketAddress(short int family, unsigned short int port,
                              unsigned long int addr)
{
    address.sin_family = family;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(addr);
}

void Socket::_assign(const Socket &socket)
{
    local_sockfd = socket.local_sockfd;
    address = socket.address;
}
