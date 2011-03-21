#include "Thread.h"
#include <QDebug>

Thread::Thread() :m_running(false) {
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
    qDebug() << "Exiting "<< thread->className() <<" :" << thread->m_thread;
    return retval;
}

void Thread::start()
{
    if (this->m_running)
        qDebug() << "Thread already started "<< this->className() <<" :" << this->m_thread ;
    else if (pthread_create(&this->m_thread, &this->m_attr, _threadFunc, static_cast<void *>(this)) != 0)
        qDebug() << "Error when creating thread "<< this->className() <<" :" << this->m_thread ;

    qDebug() << "Starting thread "<< this->className() <<" :" << this->m_thread ;
}

void Thread::stop()
{
    qDebug() << "Stopping thread "<< this->className() <<" :"<< m_thread ;
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

pthread_t Thread::threadid() {
    return m_thread;
}
