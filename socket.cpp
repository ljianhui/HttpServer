#include "socket.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

Socket::Socket(Object *parent):
    Object(parent),
    sockfd(-1),
    cliaddr_len(0)
{
    bzero(&address, sizeof(address));
    bzero(&cliaddr, sizeof(cliaddr));
}

Socket::Socket(int domain, int type, int protocol,
               Object *parent):
    Object(parent),
    cliaddr_len(0)
{
    sockfd = socket(domain, type, protocol);
    bzero(&address, sizeof(address));
    bzero(&cliaddr, sizeof(cliaddr));
}

Socket::Socket(const Socket &socket)
{
    sockfd = socket.sockfd;
    address = socket.address;
    cliaddr = socket.cliaddr;
    cliaddr_len = socket.cliaddr_len;
}

Socket& Socket::operator=(const Socket &socket)
{
    ::close(sockfd);
    sockfd = socket.sockfd;
    address = socket.address;
    return *this;
}

Socket::~Socket()
{
    close();
}

void Socket::initSocket(int domain, int type, int protocol)
{
    if(sockfd != -1)
    {
        sockfd = socket(domain, type, protocol);
    }
}

int Socket::bind()
{
    return ::bind(sockfd, (struct sockaddr*)&address, sizeof(address));
}

int Socket::listen(int backlog)
{
    return ::listen(sockfd, backlog);
}

int Socket::accept()
{
    return ::accept(sockfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
}

int Socket::connect()
{
    return ::connect(sockfd, (struct sockaddr*)&address, sizeof(address));
}

void Socket::close()
{
    ::close(sockfd);
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
