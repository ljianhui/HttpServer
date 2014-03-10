#include "thread.h"
#include <pthread.h>

Thread::Thread(Object *parent):
    Object(parent),
    flag(-1),
    is_running(false),
    tret(0)
{
    flag = pthread_create(&tid, NULL, _threadfunc, this);
}

Thread::~Thread()
{
    if(is_running == true)
        pthread_exit(NULL);
}

void Thread::run()
{
    ;
}

void* Thread::_threadfunc(void *arg)
{
    if(arg == NULL)
        return NULL;
    Thread *thread = static_cast<Thread*>(arg);
    thread->is_running = true;
    thread->run();
    thread->is_running = false;
    thread->exit();
    return NULL;
}











