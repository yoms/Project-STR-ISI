#ifndef THREAD_H
#define THREAD_H

#include "pthread.h"
#include "Message.h"
#include <QList>

class Thread
{
public:
    Thread(int id = 0);
    virtual ~Thread();

    virtual void start();
    virtual void stop();
    virtual void join();
    bool isRunning();
    virtual void run() = 0;
    void addMessage(Message*);

private:
    Thread(const Thread&);
    Thread& operator=(const Thread&);
    friend void *_threadFunc(void *);

protected:
    bool m_running;
    QList<Message*> m_bal;

private:
    pthread_t m_thread;
    pthread_attr_t m_attr;
    int m_threadid;

};

#endif //THREAD_H
