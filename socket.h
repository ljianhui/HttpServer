#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "object.h"
#include <sys/socket.h>
#include <netinet/in.h>

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
        int accept();
        int connect();
        int closeServer();
        int closeClient();

        void setSocketAddress(short int family, unsigned short int port,
                              const char *hostname);
        void setSocketAddress(short int family, unsigned short int port,
                              unsigned long int address);

        int sendToServer(const char *data, int data_size);
        int receiveFromServer(char *buffer, int buff_size);
        int sendToClient(const char *data, int data_size);
        int receiveFromClient(char *buffer, int buff_size);
    private:
        int sockfd;
        struct sockaddr_in address;

        int clifd;
        struct sockaddr_in cliaddr;
        size_t cliaddr_len;
};

#endif // SOCKET_H_INCLUDED
