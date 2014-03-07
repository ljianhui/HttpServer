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

        void processGetCommon(const char *data, int data_len);
        string getFileName()const;

    private:
        ServerThread(const ServerThread &sthread){}
        ServerThread& operator=(const ServerThread &sthread){return *this;}
        FILE* _openFile(const string &filename)const;
        int _getFileSize(FILE *file);

        Http http;
        HttpRequestHeader *req_ptr;
        HttpResponseHeader *res_ptr;
        HttpKeyValue *key_value_ptr;
};

#endif // SERVERTHREAD_H_INCLUDED
