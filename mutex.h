#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED

#include "object.h"
#include <pthread.h>

class Mutex: public Object
{
    public:
        Mutex(Object *parent = NULL);
        Mutex(const pthread_mutexattr_t *mutexattr, Object *parent = NULL);
        virtual ~Mutex();

        int lock();
        int tryLock();
        int unlock();
    private:
        Mutex(const Mutex &mutex){}
        Mutex& operator=(const Mutex &mutex){return *this;}
    private:
        pthread_mutex_t mutex;
        int flag;
};

#endif // MUTEX_H_INCLUDED
