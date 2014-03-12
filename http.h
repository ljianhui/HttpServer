#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <map>
#include <string>
#include "object.h"
#include "tcpsocket.h"

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

        int request(const string &header, const char *data, size_t data_len);
        int response(const HttpResponseHeader &header,
                     const char *data, size_t data_len);
        int response(const string &header, const char *data, size_t data_len);
        inline int receiveData(char *data, int data_len);

        inline int getStatusCode()const;
        inline string getStatusPhrase()const;
        inline int getBufferSize()const;

    private:
        Http(const Http &http){}
        Http& operator=(const Http &http){return *this;}

        int _sendData(const string &header, const char *data, size_t data_len);

        short int port;
        char *buffer;
        size_t buff_size;
        int status_code;
        string phrase;
        TcpSocket *tcp_ptr;
};

int Http::getStatusCode()const
{
    return status_code;
}

string Http::getStatusPhrase()const
{
    return phrase;
}

int Http::getBufferSize()const
{
    return buff_size;
}

int Http::receiveData(char *data, int data_len)
{
    return tcp_ptr->receiveData(data, data_len);
}

#endif // HTTP_H_INCLUDED
