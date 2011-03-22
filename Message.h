#ifndef MESSAGE_H
#define MESSAGE_H
class ThreadMessage;
#include "ThreadMessage.h"

class Message
{
public:
    enum TypeMessage {
        Demande,
        Arret,
        Passage,
        EstPasse
    };
    Message(ThreadMessage*, TypeMessage);
    ~Message(){}
    ThreadMessage * sender();
    void setSender(ThreadMessage*);
    TypeMessage type();
private:
    ThreadMessage * m_sender;
    TypeMessage m_type;
    Message(){}
};

#endif // MESSAGE_H
