#include "ThreadMessage.h"
#include <QDebug>
#define THREAD_SIGNAL SIGUSR1

Thread* getThreadPointer(pthread_t p);

ThreadMessage::ThreadMessage()
{
    qDebug() << this;
    this->m_timerSpecs.it_value.tv_sec = 0;
    this->m_timerSpecs.it_value.tv_nsec = 0;
    this->m_timerSpecs.it_interval.tv_sec = 0;
    this->m_timerSpecs.it_interval.tv_nsec = 0;

    pthread_mutex_init(&m_mutex,NULL);
    sigemptyset(&this->m_signalAction.sa_mask);
    this->m_signalAction.sa_flags = SA_SIGINFO;
    this->m_signalAction.sa_sigaction = ThreadMessage::_newmessage;

    if (sigaction(THREAD_SIGNAL, &this->m_signalAction, NULL))
    {
        qDebug() << "impossible de creer le handle";
    }
    qDebug() << "Thread pointer :"<< this;
}


void ThreadMessage::addMessage(Message* m)
{
    pthread_mutex_lock(&m_mutex);
    m_messageList << m;
    pthread_mutex_unlock(&m_mutex);
    pthread_kill(this->threadid(), THREAD_SIGNAL);
}

void ThreadMessage::removeMessage(){
    if(!m_messageList.isEmpty())
        m_messageList.removeFirst();
}
void ThreadMessage::_newmessage(int sigNumb, siginfo_t *si, void *uc)
{
    ThreadMessage* t = (ThreadMessage*)getThreadPointer(pthread_self());
    qDebug() << t->className() << " : " << getThreadPointer(pthread_self());
    t->newMessage();

}
