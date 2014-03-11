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

}


