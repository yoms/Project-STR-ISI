#include "Message.h"

Message::Message(Thread * t, Message::TypeMessage type):m_sender(t), m_type(type)
{
}

void Message::setSender(Thread * t){
    this->m_sender = t;
}

Message::TypeMessage Message::type(){
    return this->m_type;
}

Thread * Message::sender(){
    return this->m_sender;
}
