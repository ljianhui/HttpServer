#ifndef HTTPREQUESTHEADER_H_INCLUDED
#define HTTPREQUESTHEADER_H_INCLUDED

#include "httpheader.h"

class HttpRequestHeader : public HttpHeader
{
    public:
        enum Methods
        {
            NONE, GET, POST, HEAD, PUT, DELETE
        };
    private:
        Methods method;
};

#endif // HTTPREQUESTHEADER_H_INCLUDED
