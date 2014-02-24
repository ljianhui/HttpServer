#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "object.h"
#include <pthread.h>

class Thread : public Object
{
    public:
        Thread(Object *parent = NULL);
        Thread(void *arg, Object *parent = NULL);
        virtual ~Thread();

        void exit(int exit_code = 0);
        int wait();
        int cancel();
        bool isRunning();
        bool isFinished();

        bool operator==(const Thread &trd);
        bool operator!=(const Thread &trd);

    protected:
        virtual void run();

    private:
        Thread(const Thread &trd){}
        Thread& operator=(const Thread &trd){return *this;}

        void __run();

        pthread_t tid;
        bool is_running;
        int push_count;
};

#endif // THREAD_H_INCLUDED
