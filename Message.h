#ifndef MESSAGE_H
#define MESSAGE_H
#include "Thread.h"

class Message
{
public:
    Message(Thread*);
    Thread * sender();
    setSender(Thread*);
private:
    Thread * m_sender;
};

#endif // MESSAGE_H
