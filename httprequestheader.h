#ifndef HTTPREQUESTHEADER_H_INCLUDED
#define HTTPREQUESTHEADER_H_INCLUDED

class HttpRequestHeader: public Object
{
    public:
        HttpRequestHeader(Object *parent = NULL);
        HttpRequestHeader(const HttpRequest &hrt);
        HttpRequestHeader& operator=(const HttpRequest &hrt);
        virtual ~HttpRequestHeader();
};

#endif // HTTPREQUESTHEADER_H_INCLUDED
