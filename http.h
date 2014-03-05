#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <map>
#include <string>
#include "tcpsocket.h"
#include "object.h"

using std::string;

class HttpRequestHeader;
class HttpResponseHeader;
class HttpHeader;

class Http : public Object
{
    public:
        Http(Object *parent = NULL);
        Http(const string &host, short int port = 80, Object *parent = NULL);
        virtual ~Http();

        void setBufferSize(int size);
        void setSocket(TcpSocket* &tcp);
        void setRequestBySocket();
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
        int _sendData(const HttpHeader &header,
                      const char *data, size_t data_len);

        short int port;
        char *buffer;
        int buff_size;
        int status_code;
        string phrase;
        TcpSocket *tcp_ptr;
};

#endif // HTTP_H_INCLUDED
