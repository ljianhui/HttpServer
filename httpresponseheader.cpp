#include "httpresponseheader.h"
#include "object.h"
#include <stdlib.h>
#include <stdio.h>

HttpResponseHeader::HttpResponseHeader(Object *parent):
    HttpHeader(parent),
    status_code(-1),
    major_ver(1),
    minor_ver(1)
{
    version = _intToVersion(major_ver, minor_ver);
}

HttpResponseHeader::HttpResponseHeader(const string &header, Object *parent):
    HttpHeader(parent)
{
    setResponse(header);
}

HttpResponseHeader::HttpResponseHeader(int code, const string &txt,
                                       int major_version, int minor_version,
                                       Object *parent):
    HttpHeader(parent),
    phrase(txt),
    status_code(code),
    major_ver(major_version),
    minor_ver(minor_version)
{
    version = _intToVersion(major_ver, minor_ver);
}

HttpResponseHeader::HttpResponseHeader(const HttpResponseHeader &header):
    HttpHeader(header)
{
    _assignResponse(header);
}

HttpResponseHeader& HttpResponseHeader::operator=(const HttpResponseHeader &header)
{
    if(this != &header)
    {
        _assignResponse(header);
    }
    return *this;
}

string HttpResponseHeader::getReasonPhrase()const
{
    return phrase;
}

int HttpResponseHeader::getStatusCode()const
{
    return status_code;
}

string HttpResponseHeader::getVersion()const
{
    return version;
}

int HttpResponseHeader::getMajorVersion()const
{
    return major_ver;
}

int HttpResponseHeader::getMinorVersion()const
{
    return minor_ver;
}

void HttpResponseHeader::setResponse(int code, const string &txt,
                                     int major_version, int minor_version)
{
    status_code = code;
    phrase = txt;
    major_ver = major_version;
    minor_ver = minor_version;
    version = _intToVersion(major_ver, minor_ver);
}

void HttpResponseHeader::setResponse(const string &header)
{
    string math(" ");
    int begin_pos = 0;
    begin_pos = _setString(header, math, begin_pos, version);
    string tmp;
    begin_pos = _setString(header, math, begin_pos, tmp);
    status_code = atoi(tmp.c_str());
    math = "\r\n";
    begin_pos = _setString(header, math, begin_pos, phrase);

    _cstringToHttpheader(header.c_str()+begin_pos);

    _versionToInt(version, major_ver, minor_ver);
}

string HttpResponseHeader::toString()const
{
    string header;
    string div(" ");

    header += version;
    header += div;

    char cstr[11] = {'\0'};
    sprintf(cstr, "%d", status_code);
    header += cstr;
    header += div;

    header += phrase;
    header += "\r\n";

    header += HttpHeader::toString();
    return header;
}

void HttpResponseHeader::_assignResponse(const HttpResponseHeader &header)
{
    version = header.version;
    phrase = header.phrase;
    status_code = header.status_code;
    major_ver = header.major_ver;
    minor_ver = header.minor_ver;
}




















