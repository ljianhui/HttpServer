#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <pthread.h>
#include "object.h"

class Thread : public Object
{
    public:
        Thread(Object *parent = NULL);
        virtual ~Thread();

        inline void start();
        inline void exit(int exit_code = 0);
        inline int wait();
        inline int cancel();
        inline bool isRunning() const;
        inline bool isFinished() const;
        inline int getThreadReturn() const;

        inline bool operator==(const Thread &trd);
        inline bool operator!=(const Thread &trd);

    protected:
        virtual void run();

    private:
        Thread(const Thread &trd){}
        Thread& operator=(const Thread &trd){return *this;}

        static void* _threadfunc(void *arg);

        pthread_t tid;
        int flag;
        bool is_running;
        void *tret;
};

void Thread::start()
{
    if(!is_running)
        flag = pthread_create(&tid, NULL, _threadfunc, this);
}

void Thread::exit(int exit_code)
{
    if(flag != 0)
        return;

    pthread_exit((void*)exit_code);
}

int Thread::cancel()
{
    if(flag == 0)
        return pthread_cancel(tid);
    return -1;
}

int Thread::wait()
{
    if(flag == 0)
        return pthread_join(tid, &tret);
    return -1;
}

bool Thread::isRunning() const
{
    return is_running;
}

bool Thread::isFinished() const
{
    return !is_running;
}

int Thread::getThreadReturn() const
{
    return (int)(tret);
}

bool Thread::operator==(const Thread &trd)
{
    if(pthread_equal(tid, trd.tid) != 0)
        return true;
    return false;
}

bool Thread::operator!=(const Thread &trd)
{
    return !operator==(trd);
}

#endif // THREAD_H_INCLUDED
