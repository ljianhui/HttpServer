#ifndef HTTPREQUESTHEADER_H_INCLUDED
#define HTTPREQUESTHEADER_H_INCLUDED

#include "httpheader.h"
#include <string>

using std::string;

class HttpRequestHeader : public HttpHeader
{
    public:
        HttpRequestHeader(HttpHeader *parent = NULL);
        HttpRequestHeader(const string &method, const string &url,
                          int major_version, int minor_version,
                          HttpHeader *parent = NULL);
        HttpRequestHeader(const string &header, HttpHeader *parent = NULL);
        HttpRequestHeader(const HttpRequestHeader &header);
        HttpRequestHeader& operator=(const HttpRequestHeader &header);
        virtual ~HttpRequestHeader(){}

        string getMethod()const;
        string getUrl()const;

        virtual string getVersion()const;
        virtual int getMajorVersion()const;
        virtual int getMinorVersion()const;

        void setRequest(const string &method, const string &url,
                        int major_version, int minor_version);

        virtual string toString()const;
    private:
        string req_method;
        string req_url;
        int major_ver;
        int minor_ver;
};

#endif // HTTPREQUESTHEADER_H_INCLUDED
