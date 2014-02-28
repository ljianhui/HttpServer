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
    string math(" ");
    int begin_pos = 0;
    int end_pos = header.find(math, begin_pos);
    req_method = header.substr(begin_pos, end_pos-begin_pos);
    begin_pos = end_pos + 1;
    end_pos = header.find(math, begin_pos);
    req_url = header.substr(begin_pos, end_pos-begin_pos);

    math = "\r\n";
    begin_pos = end_pos + 1;
    end_pos = header.find(math, begin_pos);
    version = header.substr(begin_pos, end_pos - begin_pos);

    math = "\\";
    begin_pos = 0;
    end_pos = version.find(math, begin_pos);
    begin_pos = end_pos + 1;
    math = ".";

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
