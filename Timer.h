#ifndef TIMER_H
#define TIMER_H
#include "Thread.h"
#include <QList>
#include <unistd.h>
#include <signal.h>
class TimerListener
{
public:
    virtual void tick() = 0;
};

class Timer : public Thread
{
    timer_t m_timerID;
    sigset_t m_sigBlockSet;
    struct sigevent m_signalEvent;
    struct sigaction m_signalAction;
    struct itimerspec m_timerSpecs;
    QList<TimerListener*> m_listenerList;
public:
    Timer(int sec, int mSec = 0, int nSec = 0);
    void addListener(TimerListener* tl);
    void removeListener(TimerListener* tl);
    static void wait(int sec, int mSec = 0, int nSec = 0);
    void tick();
    void run();
    void stop();
private:
    static void _alarmFunction(int sigNumb, siginfo_t *si, void *uc);
    Timer(){}
};

#endif // TIMER_H
