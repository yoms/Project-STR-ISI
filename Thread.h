#ifndef THREAD_H
#define THREAD_H

#include "pthread.h"
#include <QString>

class Thread
{

public:
    Thread();
    virtual ~Thread();

    virtual void start();
    virtual void stop();
    virtual void join();
    bool isRunning();
    virtual void run() = 0;
    virtual QString className(){ return QString("Thread");}

private:
    Thread(const Thread&);
    Thread& operator=(const Thread&);
    friend void *_threadFunc(void *);

protected:
    bool m_running;

private:
    pthread_t m_thread;
    pthread_attr_t m_attr;

};

#endif //THREAD_H
