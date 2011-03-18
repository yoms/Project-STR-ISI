#include "Message.h"

Message::Message(Thread * t)
{
    this->m_sender = t;
}

Message::setSender(Thread * t){
    this->m_sender = t;
}

Thread * Message::sender(){
    return this->m_sender;
}
