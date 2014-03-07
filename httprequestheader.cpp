#include "httprequestheader.h"
#include <stdio.h>
#include <stdlib.h>

HttpRequestHeader::HttpRequestHeader(Object *parent):
    HttpHeader(parent),
    major_ver(1),
    minor_ver(1)
{
    version = _intToVersion(major_ver, minor_ver);
}

HttpRequestHeader::HttpRequestHeader(const string &method, const string &url,
                                     int major_version, int minor_version,
                                     Object *parent):
    HttpHeader(parent),
    req_method(method),
    req_url(url),
    major_ver(major_version),
    minor_ver(minor_version)
{
    version = _intToVersion(major_ver, minor_ver);
}

void HttpRequestHeader::_assignRequest(const HttpRequestHeader &header)
{
    req_method = header.req_method;
    req_url = header.req_url;
    version = header.version;
    major_ver = header.major_ver;
    minor_ver = header.minor_ver;
}



HttpRequestHeader::HttpRequestHeader(const string &header, Object *parent):
    HttpHeader(parent)
{
    setRequest(header);
}

HttpRequestHeader::HttpRequestHeader(const HttpRequestHeader &header):
    HttpHeader(header)
{
    _assignRequest(header);
}

HttpRequestHeader& HttpRequestHeader::operator=(const HttpRequestHeader &header)
{
    if(this != &header)
    {
        _assignRequest(header);
    }
    return *this;
}

string HttpRequestHeader::getVersion()const
{
    return version;
}

int HttpRequestHeader::getMajorVersion()const
{
    return major_ver;
}

int HttpRequestHeader::getMinorVersion()const
{
    return minor_ver;
}

void HttpRequestHeader::setRequest(const string &method, const string &url,
                                   int major_version, int minor_version)
{
    req_method = method;
    req_url = url;
    major_ver = major_version;
    minor_ver = minor_version;
    version = _intToVersion(major_ver, minor_ver);
}

void HttpRequestHeader::setRequest(const string &header)
{
    string math(" ");
    int begin_pos = 0;
    begin_pos = _setString(header, math, begin_pos, req_method);
    begin_pos = _setString(header, math, begin_pos, req_url);
    math = "\r\n";
    begin_pos = _setString(header, math, begin_pos, version);//version = "HTTP/1.1"

    _cstringToHttpheader(header.c_str() + begin_pos);

    _versionToInt(version, major_ver, minor_ver);
}

string HttpRequestHeader::toString()const
{
    string header;
    string div(" ");
    header += req_method;
    header += div;
    header += req_url;
    header += div;
    header += version;
    header += "\r\n";
    header += HttpHeader::toString();
    return header;
}
