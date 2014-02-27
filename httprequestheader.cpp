#include "httprequestheader.h"
#include <stdio.h>

HttpRequestHeader::HttpRequestHeader(HttpHeader *parent):
    HttpHeader(parent),
    major_ver(1),
    minor_ver(1)
{
}

HttpRequestHeader::HttpRequestHeader(const string &method, const string &url,
                                     int major_version, int minor_version,
                                     HttpHeader *parent):
    HttpHeader(parent),
    req_method(method),
    req_url(url),
    major_ver(major_version),
    minor_ver(minor_version)
{
}

HttpRequestHeader::HttpRequestHeader(const string &header, HttpHeader *parent):
    HttpHeader(parent)
{

}

HttpRequestHeader::HttpRequestHeader(const HttpRequestHeader &header):
    HttpHeader(header)
{

}

HttpRequestHeader& HttpRequestHeader::operator=(const HttpRequestHeader &header)
{

}

string HttpRequestHeader::getVersion()const
{
}

int HttpRequestHeader::getMajorVersion()const
{
}

int HttpRequestHeader::getMinorVersion()const
{
}

string HttpRequestHeader::getMethod()const
{
}

string HttpRequestHeader::getUrl()const
{
}

void HttpRequestHeader::setRequest(const string &method, const string &url,
                                   int major_version, int minor_version)
{
}

string HttpRequestHeader::toString()const
{
}
