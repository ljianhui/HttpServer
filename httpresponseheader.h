#ifndef HTTPRESPONSEHEADER_H_INCLUDED
#define HTTPRESPONSEHEADER_H_INCLUDED

#include "httpheader.h"
#include <string>

using std::string;

class HttpResponseHeader : public HttpHeader
{
    public:
        HttpResponseHeader(Object *parent = NULL);
        HttpResponseHeader(const string &header, Object *parent = NULL);
        HttpResponseHeader(int code, const string &txt,
                           int major_version = 1, int minor_version = 1,
                           Object *parent = NULL);
        HttpResponseHeader(const HttpResponseHeader &header);
        HttpResponseHeader& operator=(const HttpResponseHeader &header);
        virtual ~HttpResponseHeader(){}

        string getReasonPhrase()const;
        int getStatusCode()const;

        virtual string getVersion()const;
        virtual int getMinorVersion()const;
        virtual int getMajorVersion()const;

        void setResponse(int code, const string &txt,
                         int major_version, int minor_version);

        virtual string toString()const;

    private:
        void _assignResponse(const HttpResponseHeader &header);

        string version;
        string phrase;
        int status_code;
        int major_ver;
        int minor_ver;
};



#endif // HTTPRESPONSEHEADER_H_INCLUDED
