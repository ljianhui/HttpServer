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
    sem_init(&finished_sem, 0, 0);
}

Thread::~Thread()
{
    sem_wait(&finished_sem);
    sem_destroy(&finished_sem);
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
    sem_post(&thread->finished_sem);
    return NULL;
}











