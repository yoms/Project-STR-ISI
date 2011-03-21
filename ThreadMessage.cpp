#include "ThreadMessage.h"

ThreadMessage::ThreadMessage()
{
}


void ThreadMessage::addMessage(Message* m)
{
    m_bal << m;
}
