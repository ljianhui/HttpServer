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
#include "commonfunction.h"

using namespace std;
//using CommonFunction::GetCurrentTime;

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
    sleep(1);
    cout << "ThreadA is running" << endl;
}

class ThreadB : public Thread
{
    protected:
        virtual void run();
};

void ThreadB::run()
{
    sleep(1);
    cout << "ThreadB is running" << endl;
}

class Test
{
    public:
    Test()
    {
        n = 10;
    }
    int getN()const
    {
        return n;
    }
    ~Test()
    {
        sleep(10);
    }
    private:
    int n;
};

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

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(80);

	bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	listen(server_sockfd, 5);

	signal(SIGCHLD, SIG_IGN);

	while(1)
	{
		string data;
		client_len = sizeof(client_addr);
		printf("Server waiting\n");

		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);

		if(fork() == 0)
		{
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

//    for(int i = 0; i < 10; ++i)
//    {
////        ThreadA *tha = new ThreadA;
////        ThreadB *thb = new ThreadB;
////        delete tha;
////        delete thb;
//        ThreadA tha;
//        ThreadB thb;
//        tha.wait();
//        thb.wait();
//        sleep(1);
//    }
//    cout << "For end" << endl;
//    sleep(3);

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
//    int i = 0;
//    pthread_create(&tid, NULL, func, &i);
//    sleep(1);
//    i = 2;
//    sleep(10);
//    pthread_join(tid, NULL);

//    Test *tp = NULL;
//    {
//        Test *t = new Test;
//        tp = t;
//        delete t;
//    }
//    int a = 11;
//    int b = 12;
//    int c = 13;
//    cout << tp->getN() << endl;

    int n = 10;
    cout << CommonFunction::IntToString(n)<<endl;
    string s = "100";
    cout << CommonFunction::StringToInt(s) << endl;
    cout << CommonFunction::GetCurrentTime() << endl;
    return 0;

}
