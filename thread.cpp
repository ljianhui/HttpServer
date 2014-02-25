#include "thread.h"
#include <pthread.h>

void* Run(void *arg);
Thread::Thread(Object *parent):
    Object(parent),
    flag(-1),
    is_running(false),
    tret(NULL)
{
    flag = pthread_create(&tid, NULL, Run, this);
}

Thread::~Thread()
{
    pthread_exit((void*)0);
}

void Thread::run()
{
    ;
}

void* Run(void *arg)
{
    Thread *thread = static_cast<Thread*>(arg);
    thread->is_running = true;
    thread->run();
    thread->is_running = false;
    return NULL;
}











