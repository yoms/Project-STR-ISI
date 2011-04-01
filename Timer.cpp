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

#include "Timer.h"
#include <QDebug>
Timer::Timer(int sec, int mSec, int nSec): Thread()
{
    this->m_timerSpecs.it_value.tv_sec = sec;
    this->m_timerSpecs.it_value.tv_nsec = mSec * 1000000 + nSec;
    this->m_timerSpecs.it_interval.tv_sec = sec;
    this->m_timerSpecs.it_interval.tv_nsec = mSec * 1000000 + nSec;

    sigemptyset(&this->m_signalAction.sa_mask);
    this->m_signalAction.sa_flags = SA_SIGINFO;
    this->m_signalAction.sa_sigaction = Timer::_alarmFunction;
    memset(&this->m_signalEvent, 0, sizeof(this->m_signalEvent));
    this->m_signalEvent.sigev_notify = SIGEV_SIGNAL;
    this->m_signalEvent.sigev_value.sival_ptr = (void*) this;
    this->m_signalEvent.sigev_signo = SIGALRM;

    if(timer_create(CLOCK_REALTIME, &this->m_signalEvent, &this->m_timerID) != 0) {
        qDebug() << "Impossible de creer le timer";
        return;
    }
    if(sigaction(SIGALRM, &this->m_signalAction, NULL)) {
        qDebug() << "impossible de creer le handle";
    }
}

void Timer::addListener(TimerListener* tl)
{
    m_listenerList << tl;
}
void Timer::removeListener(TimerListener *tl)
{
    m_listenerList.removeAll(tl);
}
void Timer::tick()
{
    for(int i = 0 ; i < m_listenerList.size(); i++)
        m_listenerList[i]->tick();
}

void Timer::run()
{
    if(timer_settime(this->m_timerID, 0, &this->m_timerSpecs, NULL) == -1)
        qDebug() << "Erreur timer:";
}
void Timer::stop()
{
    Thread::stop();
    timer_delete(this->m_timerID);
    m_listenerList.clear();
}

void Timer::_alarmFunction(int sigNumb, siginfo_t *si, void *uc)
{
    Timer * ptrTimer = reinterpret_cast<Timer *>(si->si_value.sival_ptr);
    ptrTimer->tick();
}
Timer::~Timer()
{
    timer_delete(this->m_timerID);
    m_listenerList.clear();
}
