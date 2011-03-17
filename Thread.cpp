#include "Thread.h"
#include <QDebug>

Thread::Thread(int id) :m_running(false), m_threadid(id) {
    size_t stacksize;
    pthread_attr_init(&m_attr);
    pthread_attr_getstacksize(&m_attr, &stacksize);
    stacksize *= 2;
    pthread_attr_setstacksize(&m_attr, stacksize);
}

Thread::~Thread() { }

void *_threadFunc(void *obj)
{
    void *retval = 0;
    Thread *thread = static_cast<Thread *> (obj);
    thread->m_running = true;
    thread->run();
    thread->m_running = false;
    qDebug() << "Exiting thread :" + thread->m_threadid;
    return retval;
}

void Thread::start()
{
    qDebug() << "Starting thread: " + this->m_threadid ;
    if (this->m_running)
        qDebug() << "Thread already started: " + this->m_threadid ;
    else if (pthread_create(&this->m_thread, &this->m_attr, _threadFunc, static_cast<void *>(this)) != 0)
        qDebug() << "Error when creating thread: " + this->m_threadid ;
}

void Thread::stop()
{
    qDebug() << "Stopping thread: " + m_threadid ;
    pthread_cancel(m_thread);
    m_running = false;
}

void Thread::join()
{
    //wait for the running thread to exit
    void *retValue;
    //pthread_attr_destroy(&m_attr);
    m_running = false;
    if (pthread_join(m_thread, &retValue) == 0)
    {
    }
}

bool Thread::isRunning()
{
    return m_running;
}

void Thread::addMessage(Message * m)
{
    this->m_bal.append(m);
}
