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

#include "ThreadWithMessages.h"
#include <QDebug>
#define THREAD_SIGNAL SIGUSR1

Thread* getThreadPointer(pthread_t p);

ThreadWithMessages::ThreadWithMessages()
{
    pthread_mutex_init(&m_mutex,NULL);
    sigemptyset(&this->m_signalAction.sa_mask);
    this->m_signalAction.sa_flags = SA_SIGINFO;
    this->m_signalAction.sa_sigaction = ThreadWithMessages::_newmessage;

    if (sigaction(THREAD_SIGNAL, &this->m_signalAction, NULL))
    {
        qDebug() << "impossible de creer le handle";
    }
}


void ThreadWithMessages::addMessage(Message* m)
{
    pthread_mutex_lock(&m_mutex);
    m_messageList << m;
    pthread_mutex_unlock(&m_mutex);
    pthread_kill(this->threadid(), THREAD_SIGNAL);
}

void ThreadWithMessages::removeMessage(){
    if(!m_messageList.isEmpty())
        m_messageList.removeFirst();
}
void ThreadWithMessages::_newmessage(int sigNumb, siginfo_t *si, void *uc)
{
    ThreadWithMessages* t = (ThreadWithMessages*)getThreadPointer(pthread_self());
    t->handleNewMessage();

}
