#include "Message.h"

Message::Message(Thread * t):m_sender(t)
{
}

void Message::setSender(Thread * t){
    this->m_sender = t;
}

Thread * Message::sender(){
    return this->m_sender;
}
