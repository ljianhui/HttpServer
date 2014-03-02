#ifndef HOSTADDRESS_H_INCLUDED
#define HOSTADDRESS_H_INCLUDED

#include <netinet/in.h>

class HostAddress : public Object
{
    public:
        HostAddress(Object *parent = NULL);
        HostAddress(int addr, Object *parent = NULL);
        HostAddress(const sockaddr &addr, Object *parent = NULL);
        HostAddress(const string &addr, Object *parent = NULL);
        ~HostAddress();

    private:
        struct sockaddr_in address;
};

#endif // HOSTADDRESS_H_INCLUDED
