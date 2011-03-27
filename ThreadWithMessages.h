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

#ifndef THREADWITHMESSAGES_H
#define THREADWITHMESSAGES_H
#include <Thread.h>
class Message;
#include "Message.h"
#include <QList>
#include <signal.h>
#include <sys/wait.h>
#include "pthread.h"

/**
 * @brief Représente un thread avec une boite à messages.
 */
class ThreadWithMessages : public Thread
{
public:
    /**
     * @brief Construit un thread avec une boite à messages.
     */
    ThreadWithMessages();
    virtual ~ThreadWithMessages();
    /**
     * @brief Ajoute un message à la boite à messages.
     * @param un nouveau message
     */
    void addMessage(Message*);
protected:
    void removeMessage();
    virtual void handleNewMessage() = 0;
private:
    static void _newmessage(int sigNumb, siginfo_t *si, void *uc);

protected:
    QList<Message*> m_messageList;
private:
    pthread_mutex_t m_mutex;
    timer_t m_timerID;
    struct sigevent m_signalEvent;
    struct sigaction m_signalAction;
    struct itimerspec m_timerSpecs;
};
#endif // THREADWITHMESSAGES_H
