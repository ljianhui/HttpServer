#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "object.h"
#include <pthread.h>

class Thread : public Object
{
    public:
        friend void* Run(void *arg);
        Thread(Object *parent = NULL);
        virtual ~Thread();

        inline void exit(int exit_code = 0);
        inline int wait();
        inline int cancel();
        inline bool isRunning() const;
        inline bool isFinished() const;
        inline void* getThreadReturn() const;

        inline bool operator==(const Thread &trd);
        inline bool operator!=(const Thread &trd);

    protected:
        virtual void run();

    private:
        Thread(const Thread &trd){}
        Thread& operator=(const Thread &trd){return *this;}

        pthread_t tid;
        int flag;
        volatile bool is_running;
        void *tret;
};

void Thread::exit(int exit_code)
{
    if(flag == 0)
        pthread_exit((void*) exit_code);
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

void* Thread::getThreadReturn() const
{
    return tret;
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
