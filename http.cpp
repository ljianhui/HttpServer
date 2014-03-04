#include "http.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"

Http::Http(Object *parent):
    Object(parent),
    port(80),
    buffer(NULL),
    buff_size(0),
    tcp_ptr(NULL),
    req_header(new HttpRequestHeader(this)),
    res_header(new HttpResponseHeader(this))
{

}

Http::Http(const string &host, Object *parent):
    Object(parent),
    port(80),
    buffer(NULL),
    buff_size(0),
    req_header(new HttpRequestHeader(this)),
    res_header(new HttpResponseHeader(this))
{

}

Http::Http(const string &host, short int http_port, Object *parent):
    Object(parent),
    port(http_port),
    buffer(NULL),
    buff_size(0),
    req_header(new HttpRequestHeader(this)),
    res_header(new HttpResponseHeader(this))
{

}

Http::~Http()
{
    delete []buffer;
}


void Http::setPort(int http_port)
{

}

void Http::setBufferSize(int size)
{

}

int Http::closeHttp()
{

}

int Http::request(const HttpRequestHeader &header,
                  const char *data, size_t data_len)
{

}

int Http::response(const HttpResponseHeader &header,
                   const char *data, size_t data_len)
{

}

int Http::getStatusCode()const
{

}

string Http::getStatusPhrase()const
{

}

