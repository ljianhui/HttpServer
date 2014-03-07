#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "socket.h"

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
    bzero(&acc_sock.address, sizeof(acc_sock.address));
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
    }
    return res;
}

void Socket::setSocketAddress(short int family, const char *hostname,
                              unsigned short int port)
{
    address.sin_family = family;
    address.sin_port = htons(port);
    inet_pton(family, hostname, &address.sin_addr);
}

void Socket::setSocketAddress(short int family, unsigned long int addr,
                              unsigned short int port)
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

int Socket::getLocalAddress(sockaddr *addr)const
{
    if(addr == NULL)
        return -1;
    socklen_t addr_len = sizeof(*addr);
    int res = getsockname(local_sockfd, addr, &addr_len);
    if(res == 0)
        return addr_len;
    return -1;
}

int Socket::getPeerAddress(sockaddr *addr)const
{
    if(addr == NULL)
        return -1;
    socklen_t addr_len = sizeof(*addr);
    int res = getpeername(local_sockfd, addr, &addr_len);
    if(res == 0)
        return addr_len;
    return -1;
}
