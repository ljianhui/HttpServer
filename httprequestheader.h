#ifndef HTTPREQUESTHEADER_H_INCLUDED
#define HTTPREQUESTHEADER_H_INCLUDED

#include "httpheader.h"
#include <string>

using std::string;

class HttpRequestHeader : public HttpHeader
{
    public:
        HttpRequestHeader(Object *parent = NULL);
        HttpRequestHeader(const string &method, const string &url,
                          int major_version, int minor_version,
                          Object *parent = NULL);
        HttpRequestHeader(const string &header, Object *parent = NULL);
        HttpRequestHeader(const HttpRequestHeader &header);
        HttpRequestHeader& operator=(const HttpRequestHeader &header);
        virtual ~HttpRequestHeader(){}

        inline string getMethod()const;
        inline string getUrl()const;

        virtual string getVersion()const;
        virtual int getMajorVersion()const;
        virtual int getMinorVersion()const;

        void setRequest(const string &method, const string &url,
                        int major_version, int minor_version);
        void setRequest(const string &header);

        virtual string toString()const;
    private:
        void _assignRequest(const HttpRequestHeader &header);

        string req_method;
        string req_url;
        string version;
        int major_ver;
        int minor_ver;
};

string HttpRequestHeader::getMethod()const
{
    return req_method;
}

string HttpRequestHeader::getUrl()const
{
    return req_url;
}

#endif // HTTPREQUESTHEADER_H_INCLUDED
