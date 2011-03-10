#include "Timer.h"
#include <QDebug>
Timer::Timer(int sec, int mSec, int nSec): Thread()
{
    this->m_timerSpecs.it_value.tv_sec = sec;
    this->m_timerSpecs.it_value.tv_nsec = mSec*1000000 + nSec;
    this->m_timerSpecs.it_interval.tv_sec = sec;
    this->m_timerSpecs.it_interval.tv_nsec = mSec*1000000 + nSec;

    sigemptyset(&this->m_signalAction.sa_mask);
    this->m_signalAction.sa_flags = SA_SIGINFO;
    this->m_signalAction.sa_sigaction = Timer::_alarmFunction;
    memset(&this->m_signalEvent, 0, sizeof(this->m_signalEvent));
    this->m_signalEvent.sigev_notify = SIGEV_SIGNAL;
    this->m_signalEvent.sigev_value.sival_ptr = (void*) this;
    this->m_signalEvent.sigev_signo = SIGALRM;

    if (timer_create(CLOCK_REALTIME, &this->m_signalEvent, &this->m_timerID)!= 0)
    {
        qDebug() << "Impossible de creer le timer";
        return;
    }
    if (sigaction(SIGALRM, &this->m_signalAction, NULL))
    {
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
    foreach(TimerListener* tl, m_listenerList)
        tl->tick();
}

void Timer::run()
{
    if (timer_settime(this->m_timerID, 0, &this->m_timerSpecs, NULL) == -1)
        qDebug() << "Erreur timer:";
}
void Timer::stop()
{
    Thread::stop();
    m_listenerList.clear();
    timer_delete(this->m_timerID);
}

void Timer::_alarmFunction(int sigNumb, siginfo_t *si, void *uc)
{
    Timer * ptrTimer = reinterpret_cast<Timer *> (si->si_value.sival_ptr);
    ptrTimer->tick();
}
