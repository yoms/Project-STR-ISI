#ifndef THREADMESSAGE_H
#define THREADMESSAGE_H
#include <Thread.h>
class Message;
#include "Message.h"
#include <QList>
#include <signal.h>
#include <sys/wait.h>

class ThreadMessage : public Thread
{
    enum typeMessage {
        Passage
    };

public:
    ThreadMessage();
    void addMessage(Message*);

protected:
    static void _obstacleFunction(int sigNumb, siginfo_t *si, void *uc);
protected:
    struct sigaction m_signalAction;
private:
    QList<Message*> m_bal;
};

#endif // THREADMESSAGE_H
