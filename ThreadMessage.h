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
    static void _obstacleFunction(int sigNumb, siginfo_t *si, void *uc);
    void removeMessage();
protected:
    struct sigaction m_signalAction;
protected:
    QList<Message*> m_bal;
    int m_newMessage;
private:
    pthread_mutex_t m_mutex;
};

#endif // THREADMESSAGE_H
