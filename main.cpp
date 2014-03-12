#include "tcpsocket.h"
#include "httprequestheader.h"
#include "httpresponseheader.h"
#include "httpkeyvalue.h"
#include "commonfunction.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

HttpKeyValue *key_value_ptr = HttpKeyValue::create();

void RecvRequest(TcpSocket &tcp, string &data);
void ProcessGet(TcpSocket &tcp, const HttpRequestHeader &request,
                HttpResponseHeader &response);

int main()
{

    TcpSocket tcp;
    tcp.setSocketAddress(AF_INET, (unsigned long int)INADDR_ANY, (unsigned short int)80);
    tcp.bind();
    tcp.listen(10);
    TcpSocket client;
    HttpRequestHeader request;
    HttpResponseHeader response;
    while(true)
    {
        tcp.accept(client);
        string data;
        RecvRequest(client, data);
        request.setRequest(data);
        if(request.getMethod() == "GET")
            ProcessGet(client, request, response);
        client.closeSocket();
    }
    return 0;

}

void RecvRequest(TcpSocket &tcp, string &data)
{
    const int buff_size = 1024;
    char buffer[buff_size + 1];
    int recv_bytes = 0;
    while(recv_bytes != -1)
    {
        recv_bytes = tcp.receiveData(buffer, buff_size);
        if(recv_bytes != -1)
        {
            buffer[recv_bytes] = '\0';
            data += buffer;
        }
    }
}

void ProcessGet(TcpSocket &tcp, const HttpRequestHeader &request,
                HttpResponseHeader &response)
{
    string path = request.getUrl();
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
    char *content = new char[file_len];
    file.read(content, file_len);
    string resp_head;
    response.setResponse(status_code, phrase,
                         request.getMajorVersion(), request.getMinorVersion());
    response.addValue("Connection","close");
    response.addValue("Data", CommonFunction::CurrentTime());
    response.addValue("Server", "MyHttpServer");
    response.addValue("Content-Length", CommonFunction::IntToString(file_len));
    response.addValue("Content-Type", content_type);
    string data = response.toString();
    data += content;
    tcp.sendData(data.c_str(), data.length());
    file.close();
    delete []content;
}
