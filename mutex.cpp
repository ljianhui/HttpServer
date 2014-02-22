#include "mutex.h"
#include <stdio.h>

Mutex::Mutex(Object *parent):
    Object(parent)
{
    flag = pthread_mutex_init(&mutex, NULL);
    if(flag != 0)
    {
        perror("Mutex initialization failed\n");
    }
}

Mutex::Mutex(const pthread_mutexattr_t *mutexattr, Object *parent):
    Object(parent)
{
    flag = pthread_mutex_init(&mutex, mutexattr);
    if(flag != 0)
    {
        perror("Mutex initialization failed\n");
    }
}

Mutex::~Mutex()
{
    if(flag == 0)
        pthread_mutex_destroy(&mutex);
}

int Mutex::lock()
{
    if(flag == 0)
    {
        return pthread_mutex_lock(&mutex);
    }
    else
    {
        return -1;
    }
}

int Mutex::unlock()
{
    if(flag == 0)
    {
        return pthread_mutex_lock(&mutex);
    }
    else
    {
        return -1;
    }
}
