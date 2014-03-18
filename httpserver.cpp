#include <pthread.h>
#include <fstream>
#include "httpserver.h"
#include "http.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"
#include "commonfunction.h"
#include "httpkeyvalue.h"
#include "logfile.h"

using std::ifstream;

HttpServer::HttpServer(Object *parent):
    TcpSocket(parent),
    root_dir("."),
    logfilename("./logfile"),
    key_value_ptr(HttpKeyValue::create())
{
}

HttpServer::~HttpServer()
{
    delete key_value_ptr;
}

bool HttpServer::createServer(void *arg)
{
    Parameter *ptr = new Parameter;
    ptr->server = this;
    ptr->tcp = static_cast<TcpSocket*>(arg);

    pthread_t tid;
    int res = pthread_create(&tid, NULL, _threadFunc, ptr);
    if(res != 0)
        return false;
    return true;
}

void* HttpServer::_threadFunc(void *arg)
{
    HttpRequestHeader request;
    HttpResponseHeader response;
    Http http;
    string data;

    Parameter *parameter = static_cast<Parameter*>(arg);
    HttpServer *server = parameter->server;
    TcpSocket *tcp = parameter->tcp;

    LogFile logfile(server->logfilename);

    http.setSocket(tcp);
    server->_recvRequest(http, data);
    request.setRequest(data);

    logfile.addLog(data);

    if(request.getMethod() == "GET")
        server->_processGet(http, request, response);

    delete parameter->tcp;
    delete parameter;
    pthread_exit(NULL);
}

void HttpServer::_recvRequest(Http &http, string &data)
{
    const int buff_size = 1024;
    char buffer[buff_size+1] = {'\0'};
    int recv_bytes = 0;
    while(true)
    {
        recv_bytes = http.receiveData(buffer, buff_size);
        if(recv_bytes != -1)
        {
            buffer[recv_bytes] = '\0';
            data += buffer;
        }
        else
            break;
    }
}

void HttpServer::_processGet(Http &http, const HttpRequestHeader &request,
                             HttpResponseHeader &response)
{
    string path = request.getUrl();
    string filename = CommonFunction::FileName(path);
    string filetype = CommonFunction::FileType(filename);
    string content_type = key_value_ptr->getContentType(filetype);

    string desc_file = root_dir + path;
    ifstream filestream(desc_file.c_str(), ifstream::in);
    int status_code = 200;
    size_t file_len = 0;
    char *content = NULL;

    if(!filestream)
    {
        status_code = 404;
        string notfoundfile = root_dir + "/notfound.html";
        filestream.open(notfoundfile.c_str());
    }

    file_len = CommonFunction::FileLength(filestream);
    content = new char[file_len];
    filestream.read(content, file_len);
    filestream.close();

    string phrase = key_value_ptr->getReasonPhrase(status_code);

    response.setResponse(status_code, phrase,
                         request.getMajorVersion(), request.getMinorVersion());
    response.addValue("Connection","close");
    response.addValue("Data", CommonFunction::CurrentTime());
    response.addValue("Server", "MyHttpServer");
    response.addValue("Content-Length", CommonFunction::IntToString(file_len));
    response.addValue("Content-Type", content_type);
    http.response(response, content, file_len);
    delete []content;
    content = NULL;
}

