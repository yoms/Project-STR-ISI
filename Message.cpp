#include "Message.h"

Message::Message(ThreadMessage *t , TypeMessage type):m_sender(t), m_type(type)
{
}

void Message::setSender(ThreadMessage * t){
    this->m_sender = t;
}

Message::TypeMessage Message::type(){
    return this->m_type;
}

ThreadMessage * Message::sender(){
    return this->m_sender;
}
