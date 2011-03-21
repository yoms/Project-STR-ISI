#include "ThreadMessage.h"
#include <QDebug>

ThreadMessage::ThreadMessage():m_newMessage(0)
{
    pthread_mutex_init(&m_mutex,NULL);
}


void ThreadMessage::addMessage(Message* m)
{
    pthread_mutex_lock(&m_mutex);
    m_bal << m;
    m_newMessage++;
    qDebug()<<"new Message";
    pthread_mutex_unlock(&m_mutex);
}

void ThreadMessage::removeMessage(){
    if(!m_bal.isEmpty())
        m_bal.removeFirst();
}
