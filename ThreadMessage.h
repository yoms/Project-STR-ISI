#ifndef THREADMESSAGE_H
#define THREADMESSAGE_H
#include <Thread.h>
class Message;
#include "Message.h"
#include <QList>
#include <signal.h>
#include <sys/wait.h>
#include "pthread.h"

class ThreadMessage : public Thread
{


public:
    ThreadMessage();
    void addMessage(Message*);
protected:
    void removeMessage();
    virtual void newMessage() = 0;
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
#endif // THREADMESSAGE_H
