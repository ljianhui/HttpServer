#ifndef HTTPSERVER_H_INCLUDED
#define HTTPSERVER_H_INCLUDED

#include <string>
#include "tcpsocket.h"

using std::string;

class Http;
class HttpRequestHeader;
class HttpResponseHeader;
class HttpKeyValue;

class HttpServer : public TcpSocket
{
    public:
        HttpServer(Object *parent = NULL);
        virtual ~HttpServer();

        bool createServer(void *arg);
        inline void setRootDir(const string &path);
        inline void setLogFileName(const string &path);

    private:
        HttpServer(const HttpServer &server){}
        HttpServer& operator=(const HttpServer &server){return *this;}

        static void* _threadFunc(void *arg);
        void _recvRequest(Http &http, string &data);
        void _processGet(Http &http, const HttpRequestHeader &request,
                         HttpResponseHeader &resopnse);

        struct Parameter
        {
            HttpServer *server;
            TcpSocket *tcp;
        };

        string root_dir;
        string logfilename;
        HttpKeyValue *key_value_ptr;

};

void HttpServer::setRootDir(const string &path)
{
    root_dir = path;
}

void HttpServer::setLogFileName(const string &path)
{
    logfilename = path;
}

#endif // HTTPSERVER_H_INCLUDED
