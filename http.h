#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <map>
#include <string>
#include "tcpsocket.h"
#include "object.h"

using std::string;

class HttpRequestHeader;
class HttpResponseHeader;

class Http : public Object
{
    public:
        Http(Object *parent = NULL);
        Http(const string &host, Object *parent = NULL);
        Http(const string &host, short int port, Object *parent = NULL);
        virtual ~Http();

        void setPort(int http_port = 80);
        void setBufferSize(int size);
        int closeHttp();
        int request(const HttpRequestHeader &header,
                    const char *data, size_t data_len);
        int response(const HttpResponseHeader &header,
                     const char *data, size_t data_len);

        int getStatusCode()const;
        string getStatusPhrase()const;

    private:
        Http(const Http &http){}
        Http& operator=(const Http &http){return *this;}

        int port;
        char *buffer;
        int buff_size;
        TcpSocket *tcp_ptr;
        HttpRequestHeader *req_header;
        HttpResponseHeader *res_header;
};

#endif // HTTP_H_INCLUDED
