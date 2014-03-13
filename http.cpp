#include <string.h>
#include "http.h"
#include "tcpsocket.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"

Http::Http(Object *parent):
    Object(parent),
    port(80),
    buffer(NULL),
    buff_size(0),
    tcp_ptr(NULL)
{

}

Http::Http(const string &host, short int http_port, Object *parent):
    Object(parent),
    port(http_port),
    buffer(NULL),
    buff_size(0),
    tcp_ptr(NULL)
{
    tcp_ptr = new TcpSocket(this);
    tcp_ptr->setSocketAddress(AF_INET, host.c_str(), http_port);
    tcp_ptr->connectToHost();
}

Http::~Http()
{
    if(buffer != NULL)
        delete []buffer;
    if(tcp_ptr != NULL)
        delete tcp_ptr;
}

void Http::setBufferSize(int size)
{
    char *new_buff = new char[size];
    if(new_buff == NULL)
        return;

    if(buffer != NULL)
        delete []buffer;
    buffer = new_buff;
    buff_size = size;
}

void Http::setSocket(TcpSocket *tcp)
{
    if(tcp == NULL)
        return;
    if(tcp_ptr != NULL)
        delete tcp_ptr;
    tcp_ptr = tcp;
}

int Http::closeHttp()
{
    if(tcp_ptr != NULL)
        return tcp_ptr->closeSocket();
    return -1;
}

int Http::request(const HttpRequestHeader &header,
                  const char *data, size_t data_len)
{
    if(tcp_ptr == NULL || data == NULL)
        return -1;
    return _sendData(header.toString(), data, data_len);

}

int Http::request(const string &header, const char *data, size_t data_len)
{
    if(tcp_ptr == NULL || data == NULL)
        return -1;
    return _sendData(header, data, data_len);
}

int Http::response(const HttpResponseHeader &header,
                   const char *data, size_t data_len)
{
    if(tcp_ptr == NULL || data == NULL)
        return -1;
    return _sendData(header.toString(), data, data_len);
}

int Http::response(const string &header, const char *data, size_t data_len)
{
    if(tcp_ptr == NULL || data == NULL)
        return -1;

    return _sendData(header, data, data_len);
}

int Http::_sendData(const string &header, const char *data, size_t data_len)
{
    int header_len = header.length();
    if(buff_size < header_len + data_len)
        setBufferSize(header_len + data_len + 1);

    memcpy(buffer, header.c_str(), header_len);
    if(data != NULL)
        memcpy(buffer + header_len, data, data_len);
    int send_len = tcp_ptr->sendData(buffer, header_len + data_len);

    return send_len;
}

