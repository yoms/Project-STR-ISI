#ifndef TIMER_H
#define TIMER_H
#include "Thread.h"
#include <QList>
#include <signal.h>
#include <sys/wait.h>
class TimerListener
{
public:
    virtual void tick() = 0;
};

class Timer : public Thread
{
    timer_t m_timerID;
    struct sigevent m_signalEvent;
    struct sigaction m_signalAction;
    struct itimerspec m_timerSpecs;
    QList<TimerListener*> m_listenerList;
public:
    Timer(int sec, int mSec = 0, int nSec = 0);
    void addListener(TimerListener* tl);
    void removeListener(TimerListener* tl);
    void tick();
    void run();
    void stop();
    virtual QString className(){ return QString("Timer");}
private:
    static void _alarmFunction(int sigNumb, siginfo_t *si, void *uc);
    static void _waitingFunction(int sigNumb, siginfo_t *si, void *uc);
    Timer(){}
};

#endif // TIMER_H
