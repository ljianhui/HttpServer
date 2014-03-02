#include "socket.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

Socket::Socket(Object *parent):
    Object(parent),
    local_sockfd(-1),
    peer_sockfd(-1)
{
    bzero(&local_addr, sizeof(local_addr));
    bzero(&peer_addr, sizeof(peer_addr));
}

Socket::Socket(int domain, int type, int protocol,
               Object *parent):
    Object(parent),
    peer_sockfd(-1)
{
    local_sockfd = socket(domain, type, protocol);
    bzero(&local_addr, sizeof(local_addr));
    bzero(&peer_addr, sizeof(peer_addr));
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
    if(peer_sockfd != -1 && peer_sockfd != local_sockfd)
        close(peer_sockfd);
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
                  (struct sockaddr*)&local_addr,
                  sizeof(local_addr));
}

int Socket::listen(int backlog)
{
    return ::listen(local_sockfd, backlog);
}

int Socket::accept(Socket &acc_sock)
{
    bzero(&acc_sock, sizeof(acc_sock));
    acc_sock.local_sockfd = -1;

    socklen_t peer_addr_len = sizeof(peer_addr);

    peer_sockfd = ::accept(local_sockfd,
                           (struct sockaddr*)&acc_sock.peer_addr,
                           &peer_addr_len);
    acc_sock.peer_sockfd = peer_sockfd;
    return peer_sockfd;
}

int Socket::connectToHost()
{
    int res = connect(local_sockfd,
                      (struct sockaddr*)&local_addr,
                      sizeof(local_addr));
    if(peer_sockfd != -1 && peer_sockfd != local_sockfd)
        close(peer_sockfd);
    peer_sockfd = local_sockfd;
    return res;
}

int Socket::closeSocket()
{
    int res = close(local_sockfd);
    local_sockfd = -1;
    return res;
}

void Socket::setSocketAddress(short int family, unsigned short int port,
                              const char *hostname)
{
    local_addr.sin_family = family;
    local_addr.sin_port = htons(port);
    inet_pton(family, hostname, &local_addr.sin_addr);
}

void Socket::setSocketAddress(short int family, unsigned short int port,
                              unsigned long int addr)
{
    local_addr.sin_family = family;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = htonl(addr);
}

void Socket::_assign(const Socket &socket)
{
    local_sockfd = socket.local_sockfd;
    local_addr = socket.local_addr;
    peer_sockfd = socket.peer_sockfd;
    peer_addr = socket.peer_addr;
}
