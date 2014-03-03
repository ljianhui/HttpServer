#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include "tcpsocket.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"
#include "object.h"

class Http : public Object
{
    public:
        Http(Object *parent = NULL);
        Http(const string &host_name, Object *parent = NULL);
        Http(const string &host_name, short int port,
             Object *parent);
        virtual ~Http();

    private:
        Http(const Http &http){}
        Http& operator=(const Http &http){return *this;}

        int port;
        char *buffer;
        int buff_size;
};

#endif // HTTP_H_INCLUDED
