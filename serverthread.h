#ifndef SERVERTHREAD_H_INCLUDED
#define SERVERTHREAD_H_INCLUDED

#include <string>
#include <stdio.h>
#include "thread.h"
#include "http.h"

using std::string;

class TcpSocket;
class HttpRequestHeader;
class HttpResponseHeader;
class HttpHeader;
class HttpKeyValue;


class ServerThread : public Thread
{
    public:
        ServerThread(TcpSocket* &tcp, Object *parent = NULL);
        virtual ~ServerThread();

        virtual void run();

    private:
        ServerThread(const ServerThread &sthread){}
        ServerThread& operator=(const ServerThread &sthread){return *this;}

        void _processGetMethod();
        void _recvRequest(string &data);

        Http http;
        HttpRequestHeader *req_ptr;
        HttpResponseHeader *res_ptr;
        HttpKeyValue *key_value_ptr;
};

#endif // SERVERTHREAD_H_INCLUDED
