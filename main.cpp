#include <iostream>
#include <unistd.h>
#include "object.h"
#include "mutex.h"
#include "socket.h"
#include "thread.h"
#include "tcpsocket.h"
#include "httpheader.h"
#include "httprequestheader.h"
#include "http.h"
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello world!\r\n" << endl;
    cout << getpid() << endl;
    return 0;
}
