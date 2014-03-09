#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "tcpsocket.h"
#include "socket.h"
#include "thread.h"

using namespace std;

//int argc, char *argv[]

void* func(void *arg)
{
    cout << "func" << *(int*)arg << endl;
    sleep(2);
    cout << "func" << *(int*)arg << endl;
    pthread_exit(NULL);
}

class ThreadA : public Thread
{
    protected:
        virtual void run();

};

void ThreadA::run()
{
    cout << "ThreadA is running" << endl;
}

class ThreadB : public Thread
{
    protected:
        virtual void run();
};

void ThreadB::run()
{
    cout << "ThreadB is running" << endl;
}

int main()
{
//    TcpSocket tcp;
//    tcp.setSocketAddress(AF_INET, INADDR_ANY, 80);
//    tcp.bind();
//    tcp.listen(10);
//    while(1)
//    {
//        TcpSocket *socket = new TcpSocket;
//        tcp.accept(*socket);
//        ServerThread server(socket);
//    }
//    string header("HTTP/1.1 200 OK\r\n");
//    header += "Connection: close\r\n";
//    header += "Data: Thu, 03 Jul 2003 12:00:15 GMT\r\n";
//    header += "Server: Apache/1.3.0 (Unix)\r\n";
//    header += "Last-Modified: Sun, 6 May 2007 09:23:24 GMT\r\n";
//    header += "Content-Length: 6821\r\n";
//    header += "Content-Type: text/html\r\n";
//    header += "\r\n";
//
//    HttpResponseHeader response;
//    response.setResponse(header);
//    cout << response.toString();
//    cout << response.getContentType() << endl;
//    cout << response.getContentLength() << endl;
//    cout << response.getVersion() << endl;
//    cout << response.getMajorVersion() << endl;
//    cout << response.getMinorVersion() << endl;

/*
    int server_sockfd = -1;
	int client_sockfd = -1;
	socklen_t client_len = 0;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	//\u521b\u5efa\u5957\u63a5\u5b57
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;//\u6307\u5b9a\u7f51\u7edc\u5957\u63a5\u5b57
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);//\u63a5\u53d7\u6240\u6709IP\u5730\u5740\u7684\u8fde\u63a5
	server_addr.sin_port = htons(80);//\u7ed1\u5b9a\u52309736\u7aef\u53e3
	//\u7ed1\u5b9a\uff08\u547d\u540d\uff09\u5957\u63a5\u5b57
	bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	//\u521b\u5efa\u5957\u63a5\u5b57\u961f\u5217\uff0c\u76d1\u542c\u5957\u63a5\u5b57
	listen(server_sockfd, 5);
	//\u5ffd\u7565\u5b50\u8fdb\u7a0b\u505c\u6b62\u6216\u9000\u51fa\u4fe1\u53f7
	signal(SIGCHLD, SIG_IGN);

	while(1)
	{
		string data;
		client_len = sizeof(client_addr);
		printf("Server waiting\n");
		//\u63a5\u53d7\u8fde\u63a5\uff0c\u521b\u5efa\u65b0\u7684\u5957\u63a5\u5b57
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);

		if(fork() == 0)
		{
			//\u5b50\u8fdb\u7a0b\u4e2d\uff0c\u8bfb\u53d6\u5ba2\u6237\u7aef\u53d1\u8fc7\u6765\u7684\u4fe1\u606f\uff0c\u5904\u7406\u4fe1\u606f\uff0c\u518d\u53d1\u9001\u7ed9\u5ba2\u6237\u7aef
			const int buff_size = 1024;
			char buffer[buff_size + 1];
			int read_bytes = 0;
			while((read_bytes = read(client_sockfd, buffer, buff_size)) > 0)
			{
			    buffer[read_bytes] = '\0';
			    data += buffer;
			}
			cout << data << endl;
			exit(0);
		}
		else
		{
			//\u7236\u8fdb\u7a0b\u4e2d\uff0c\u5173\u95ed\u5957\u63a5\u5b57
			close(client_sockfd);
		}
	}
*/

//    TcpSocket tcp;
//    tcp.setSocketAddress(AF_INET, INADDR_ANY, 80);
//    tcp.bind();
//    tcp.listen(5);
//    while(1)
//    {
//        cout << "Server Waiting" << endl;
//        TcpSocket *tcp_ptr = new TcpSocket();
//        tcp.accept(*tcp_ptr);
//        const int buff_size = 1024;
//        char buffer[buff_size + 1];
//        int read_bytes = 0;
//        string tmp;
//        while((read_bytes = tcp.receiveData(buffer, buff_size)) > 0)
//        {
//                buffer[read_bytes] = '\0';
//                tmp += buffer;
//        }
//        cout << tmp;
//        delete tcp_ptr;
//    }

/*
    Socket sock(AF_INET, SOCK_STREAM, 0);
    unsigned short int port = 80;
    sock.setSocketAddress(AF_INET, (unsigned long int)INADDR_ANY, port);
    sock.bind();
    sock.listen(5);
    const int buff_size = 1024;
    char buffer[buff_size+1];
    int read_bytes = 0;
    while(1)
    {
        cout << "Server3 Waiting" << endl;
        Socket client;
        sock.accept(client);
        if(fork() == 0)
        {
        string tmp;
        while((read_bytes = client.receiveData(buffer, buff_size)) > 0)
        {
            buffer[read_bytes] = '\0';
            tmp += buffer;
        }
        cout << tmp;
        }
    }
*/

    for(int i = 0; i < 10; ++i)
    {
        ThreadA tha;
        ThreadB thb;
//        sleep(1);
    }
    sleep(3);

//    pthread_t tid[10];
//    for(int i = 0; i < 10; ++i)
//    {
//        pthread_create(&tid[i], NULL, func, NULL);
//    }
//    for(int i = 0; i < 10; ++i)
//    {
//        pthread_join(tid[i], NULL);
//    }

//    pthread_t tid;
//
//    int i = 0;
//    pthread_create(&tid, NULL, func, &i);
//    sleep(1);
//    i = 2;
//    pthread_join(tid, NULL);
    return 0;

}
