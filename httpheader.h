#ifndef HTTPHEADER_H_INCLUDED
#define HTTPHEADER_H_INCLUDED

#include "object.h"
#include <string>

using std::string;

class HttpHeader : public Object
{
    public:
        HttpHeader(Object *parent = NULL);
        HttpHeader(const HttpHeader &header);
        HttpHeader(const string &head);
        HttpHeader(const char *head);
        HttpHeader& operator=(const HttpHeader &header);
        virtual ~HttpHeader();

        enum Method
        {
            GET, POST, HEAD, PUT, DELETE
        };
};

#endif // HTTPHEAD_H_INCLUDED
