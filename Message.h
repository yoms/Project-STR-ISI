#ifndef MESSAGE_H
#define MESSAGE_H
class Thread;
#include "Thread.h"

class Message
{
public:
    Message(Thread*);
    ~Message(){}
    Thread * sender();
    void setSender(Thread*);
private:
    Thread * m_sender;
    Message(){}
};

#endif // MESSAGE_H
