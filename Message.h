#ifndef MESSAGE_H
#define MESSAGE_H
class Thread;
#include "Thread.h"

class Message
{
public:
    enum TypeMessage {
        Passage
    };
    Message(Thread*, TypeMessage);
    ~Message(){}
    Thread * sender();
    void setSender(Thread*);
    TypeMessage type();
private:
    Thread * m_sender;
    TypeMessage m_type;
    Message(){}
};

#endif // MESSAGE_H
