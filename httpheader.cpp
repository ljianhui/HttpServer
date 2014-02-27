#include "httpheader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using std::list;
using std::string;

HttpHeader::HttpHeader(Object *parent):
    Object(parent),
    is_vaild(false)
{

}

HttpHeader::HttpHeader(const HttpHeader &header):
    Object(header)
{
    _assign(header);
}

HttpHeader::HttpHeader(const char *header, Object *parent):
    Object(parent)
{
    _cstringToHttpheader(header);
}

HttpHeader::HttpHeader(const string &header, Object *parent):
    Object(parent)
{
    _cstringToHttpheader(header.c_str());
}

void HttpHeader::_cstringToHttpheader(const char *header)
{
    char div[] = ":";
    char end[] = "\r\n";
    while(*header != '\r')
    {
        const char *str = strstr(header, div);
        if(str == NULL || *(str+1) != ' ')
        {
            is_vaild = false;
            break;
        }
        int char_count = str - header;
        string key(header, char_count);
        keys.push_back(key);

        header = str + 2;
        str = strstr(header, end);
        if(str == NULL)
        {
            is_vaild = false;
            break;
        }
        char_count = str - header;
        string value(header, char_count);
        values.push_back(value);

        header = str + 2;
    }
    is_vaild = true;
}

void HttpHeader::_assign(const HttpHeader &header)
{
    is_vaild = header.is_vaild;
    keys = header.keys;
    values = header.values;
}

HttpHeader& HttpHeader::operator=(const HttpHeader &header)
{
    if(this != &header)
    {
        Object::operator=(header);
        _assign(header);
    }
    return *this;
}

HttpHeader::~HttpHeader()
{
    keys.clear();
    values.clear();
}

void HttpHeader::addValue(const string &key, const string &value)
{
    keys.push_back(key);
    values.push_back(value);
}

list<string>::iterator HttpHeader::_findValue(const string &key)
{
    list<string>::iterator keys_it = keys.begin();
    list<string>::iterator values_it = values.begin();
    for(; keys_it != keys.end(); ++keys_it, ++values_it)
    {
        if(*keys_it == key)
            break;
    }
    return values_it;
}

list<string>::const_iterator HttpHeader::_findValueConst(const string &key)const
{
    list<string>::const_iterator keys_it = keys.begin();
    list<string>::const_iterator values_it = values.begin();
    for(; keys_it != keys.end(); ++keys_it, ++values_it)
    {
        if(*keys_it == key)
            break;
    }
    return values_it;
}

void HttpHeader::setValue(const string &key, const string &value)
{
    list<string>::iterator it = _findValue(key);
    if(it != values.end())
        *it = value;
}

void HttpHeader::setContentLength(int len)
{
    list<string>::iterator it = _findValue("Content-Length");
    if(it == values.end())
    {
        it = _findValue("Content-length");
        if(it == values.end())
            it = _findValue("content-length");
    }
    if(it != values.end())
    {
        char tmp[11] = {'\0'};
        sprintf(tmp, "%d", len);
        string num(tmp);
        *it = num;
    }
}

void HttpHeader::setContentType(const string &type)
{
    list<string>::iterator it = _findValue("Content-Type");
    if(it == values.end())
    {
        it = _findValue("Content-type");
        if(it == values.end())
            it = _findValue("content-type");
    }
    if(it != values.end())
        *it = type;
}

string HttpHeader::getValue(const string &key) const
{
    list<string>::const_iterator it = _findValueConst(key);
    if(it != values.end())
        return *it;
    return string("");
}

int HttpHeader::getContentLength() const
{
    list<string>::const_iterator it = _findValueConst("Content-Length");
    if(it == values.end())
    {
        it = _findValueConst("Content-length");
        if(it == values.end())
            it = _findValueConst("content-length");
    }
    if(it != values.end())
    {
        int len = atoi((*it).c_str());
        return len;
    }
    return -1;
}

string HttpHeader::getContentType() const
{
    list<string>::const_iterator it = _findValueConst("Content-Type");
    if(it == values.end())
    {
        it = _findValueConst("Content-type");
        if(it == values.end())
            it = _findValueConst("content-type");
    }
    if(it != values.end())
        return *it;
    return string("");
}

bool HttpHeader::hasContentLength() const
{
    if(getContentLength() != -1)
        return true;
    return false;
}

bool HttpHeader::hasContentType() const
{
    if(getContentType() != "")
        return true;
    return false;
}

bool HttpHeader::hasKey(const string &key) const
{
    list<string>::const_iterator it = keys.begin();
    for(; it != keys.end(); ++it)
    {
        if(*it == key)
            return true;
    }
    return false;
}

void HttpHeader::removeValue(const string &key)
{
    list<string>::iterator keys_it = keys.begin();
    list<string>::iterator values_it = values.begin();
    while(keys_it != keys.end())
    {
        if(*keys_it == key)
        {
            keys.erase(keys_it);
            values.erase(values_it);
        }
        ++keys_it;
        ++values_it;
    }
}


string HttpHeader::toString() const
{
    string div(": ");
    string end("\r\n");
    string header;

    list<string>::const_iterator keys_it = keys.begin();
    list<string>::const_iterator values_it = values.begin();
    while(keys_it != keys.end())
    {
        header += *keys_it;
        header += div;
        header += *values_it;
        header += end;

        ++keys_it;
        ++values_it;
    }
    header += end;
    return header;
}
