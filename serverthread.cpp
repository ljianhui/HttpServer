#include <unistd.h>
#include <stdio.h>
#include "serverthread.h"
#include "tcpsocket.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"
#include "httpkeyvalue.h"

ServerThread::ServerThread(TcpSocket* &tcp, Object *parent):
    Thread(parent),
    req_ptr(new HttpRequestHeader(this)),
    res_ptr(new HttpResponseHeader(this)),
    key_value_ptr(HttpKeyValue::create())
{
    http.setSocket(tcp);
}

ServerThread::~ServerThread()
{
    delete key_value_ptr;
}

void ServerThread::run()
{
    const int buff_size = 1024;
    char buffer[buff_size+1] = {'\0'};
    string tmp;
    int count = 0;
    while((count = http.receiveData(buffer, buff_size)) > 0)
    {
        buffer[count] = '\0';
        tmp += buffer;
    }
    req_ptr->setRequest(tmp);
    int end_pos = tmp.find("\r\n\r\n", 0);
    if(req_ptr->getMethod() == "GET")
        processGetCommon(tmp.c_str() + end_pos + 4, tmp.length() - end_pos - 4);
}

void ServerThread::processGetCommon(const char *data, int data_len)
{
    string filename = getFileName();
    FILE *file = _openFile(filename);
    int status_code = 0;
    string phrase;
    if(file == NULL)
    {
        status_code = 404;
        phrase = key_value_ptr->getReasonPhrase(404);
    }
    else
    {
        status_code = 200;
        phrase = key_value_ptr->getReasonPhrase(200);
    }
    int filesize = _getFileSize(file);
    if(http.getBufferSize() < filesize)
        http.setBufferSize(filesize);

    char *buffer = new char[filesize];
    int readBytes = fread(buffer, filesize, 1, file);

    string header;
    header += "HTTP/1.1 ";
    char tmp[12] = {'\0'};
    sprintf(tmp, "%d", status_code);
    string num(tmp);
    header += num;
    header += " ";
    header += phrase;
    header += "\n";
    header += "Connection: close\r\n";
    header += "Server: MyHttp\r\n";
    header += "\r\n";
    res_ptr->setResponse(header);
    http.response(*res_ptr, buffer, readBytes);
}

string ServerThread::getFileName()const
{
    string url = req_ptr->getUrl();
    int begin_pos = url.find_last_of("/");
    string filename = url.substr(begin_pos+1);
    return filename;
}

FILE* ServerThread::_openFile(const string &filename)const
{
    FILE *file = fopen(filename.c_str(), "r");
    return file;
}

int ServerThread::_getFileSize(FILE *file)
{
    if(file == NULL)
        return -1;

    int pos = ftell(file);
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, pos, SEEK_SET);
    return size;
}

