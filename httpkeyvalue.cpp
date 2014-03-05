#include "httpkeyvalue.h"
#include <algorithm>

using std::map;

HttpKeyValue* HttpKeyValue::obj_ptr(NULL);
int HttpKeyValue::count(0);
Mutex HttpKeyValue::mutex;

HttpKeyValue* HttpKeyValue::create()
{
    if(obj_ptr == NULL)
    {
        mutex.lock();
        if(obj_ptr == NULL)
            obj_ptr = new HttpKeyValue;
        mutex.unlock();
    }
    mutex.lock();
    ++count;
    mutex.unlock();
    return obj_ptr;
}

HttpKeyValue::HttpKeyValue()
{
    _insertType();
    _insertError();
}

HttpKeyValue::~HttpKeyValue()
{
    mutex.lock();
    --count;
    if(count == 0)
    {
        delete obj_ptr;
        obj_ptr = NULL;
    }
    mutex.unlock();
}

string HttpKeyValue::getReasonPhrase(int code)
{
    map<int,string>::const_iterator it = error.find(code);
    if(it != error.end())
        return it->second;
    return string("");
}

string HttpKeyValue::getContentType(const string &file_type)
{
    map<string,string>::const_iterator it = type.find(file_type);
    if(it != type.end())
        return it->second;
    return string("");
}

void HttpKeyValue::_insertType()
{
    type.insert(map<string,string>::value_type("jpeg", "image/jpeg"));
    type.insert(map<string,string>::value_type("png", "image/png"));
    type.insert(map<string,string>::value_type("mpg", "video/mpeg"));
    type.insert(map<string,string>::value_type("asf", "video/x-ms-asf"));
    type.insert(map<string,string>::value_type("avi", "video/x-msvideo"));
    type.insert(map<string,string>::value_type("bmp", "image/bmp"));
    type.insert(map<string,string>::value_type("doc", "application/msword"));
    type.insert(map<string,string>::value_type("exe", "application/octet-stream"));
    type.insert(map<string,string>::value_type("rar", "application/octet-stream"));
    type.insert(map<string,string>::value_type("zip", "application/zip"));
    type.insert(map<string,string>::value_type("jpg", "image/jpeg"));
    type.insert(map<string,string>::value_type("gif", "image/gif"));
    type.insert(map<string,string>::value_type("txt", "text/plain"));
    type.insert(map<string,string>::value_type("c", "text/plain"));
    type.insert(map<string,string>::value_type("cpp", "text/plain"));
    type.insert(map<string,string>::value_type("cxx", "text/plain"));
    type.insert(map<string,string>::value_type("h", "text/plain"));
    type.insert(map<string,string>::value_type("ico", "image/x-icon"));
    type.insert(map<string,string>::value_type("css", "text/css"));
    type.insert(map<string,string>::value_type("htm", "text/html"));
    type.insert(map<string,string>::value_type("html", "text/html"));
    type.insert(map<string,string>::value_type("*", "application/octet-stream"));
}

void HttpKeyValue::_insertError()
{
    error.insert(map<int,string>::value_type(200, "OK"));
    error.insert(map<int,string>::value_type(301, "Moved Permanently"));
    error.insert(map<int,string>::value_type(400, "Bad Request"));
    error.insert(map<int,string>::value_type(404, "Not Found"));
    error.insert(map<int,string>::value_type(505, "Http Version Not Supported"));
}
