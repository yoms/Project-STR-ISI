/*
 *   Copyright 2011 by Alexandre Mendes <alex.mendes1988@gmail.com>
 *   Copyright 2011 by Bertrand Pages <pages.bertrand@gmail.com>
 *   Copyright 2011 by Guillaume Hormiere <hormiere.guillaume@gmail.com>
 *   Copyright 2011 by Nicolas Noullet <nicolas.noullet@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Thread.h"
#include <QDebug>
QMap<pthread_t,Thread*> threadMap;
pthread_mutex_t mutexThreadMap = PTHREAD_MUTEX_INITIALIZER;

void addNewThread(pthread_t p,Thread* t)
{
    pthread_mutex_lock(&mutexThreadMap);
    threadMap[p] = t;
    pthread_mutex_unlock(&mutexThreadMap);
}
Thread* getThreadPointer(pthread_t p)
{
    pthread_mutex_lock(&mutexThreadMap);
    Thread* t = threadMap[p];
    pthread_mutex_unlock(&mutexThreadMap);
    return t;
}

Thread::Thread() :m_running(false) {
    size_t stacksize;
    pthread_attr_init(&m_attr);
    pthread_attr_getstacksize(&m_attr, &stacksize);
    stacksize *= 2;
    pthread_attr_setstacksize(&m_attr, stacksize);
}

Thread::~Thread()
{
}

void *_threadFunc(void *obj)
{
    void *retval = 0;
    Thread *thread = static_cast<Thread *> (obj);
    addNewThread(pthread_self(), thread);
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
    pthread_cancel(m_thread);
    m_running = false;
}

void Thread::join()
{
    //pthread_attr_destroy(&m_attr);
    m_running = false;
    if (pthread_join(m_thread, NULL) == 0)
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
