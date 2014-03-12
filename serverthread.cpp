#include <unistd.h>
#include <fstream>
#include "serverthread.h"
#include "tcpsocket.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"
#include "httpkeyvalue.h"
#include "commonfunction.h"

using std::ifstream;

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
    string data;
    _recvRequest(data);

    req_ptr->setRequest(data);

    if(req_ptr->getMethod() == "GET")
        _processGetMethod();
}

void ServerThread::_processGetMethod()
{
    string path = req_ptr->getUrl();
    string filename = CommonFunction::FileName(path);
    string filetype = CommonFunction::FileType(filename);
    string content_type = key_value_ptr->getContentType(filetype);

    string filepath("./");
    filepath += filename;
    ifstream file(filepath.c_str(), ifstream::in);
    int status_code = 200;
    if(!file)
        status_code = 404;

    string phrase = key_value_ptr->getReasonPhrase(status_code);

    size_t file_len = CommonFunction::FileLength(file);
    if(file_len > http.getBufferSize())
        http.setBufferSize(file_len);
    char *content = new char[file_len];
    file.read(content, file_len);
    string resp_head;
    res_ptr->setResponse(status_code, phrase,
                         req_ptr->getMajorVersion(), req_ptr->getMinorVersion());
    res_ptr->addValue("Connection","close");
    res_ptr->addValue("Data", CommonFunction::CurrentTime());
    res_ptr->addValue("Server", "MyHttpServer");
    res_ptr->addValue("Content-Length", CommonFunction::IntToString(file_len));
    res_ptr->addValue("Content-Type", content_type);
    http.response(*res_ptr, content, file_len);
    http.closeHttp();
    delete []content;
}

void ServerThread::_recvRequest(string &data)
{
    const int buff_size = 1024;
    char buffer[buff_size + 1];
    int recv_bytes = 0;
    while(recv_bytes != -1)
    {
        recv_bytes = http.receiveData(buffer, buff_size);
        if(recv_bytes != -1)
        {
            buffer[recv_bytes] = '\0';
            data += buffer;
        }
    }
}

