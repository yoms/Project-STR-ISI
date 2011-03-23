#include "FeuStation.h"

FeuStation::FeuStation():m_free(false)
{
}

bool FeuStation::indiquerPassage() {
    return this->m_station->indiquerPassage();
}

void FeuStation::addStation(Station* s){
    m_station = s;
}

void FeuStation::newMessage(){
    while(m_messageList.size())
    {
        Message* m = m_messageList.takeFirst();
        switch(m->type()){
        case Message::Demande:
        {
            if(m_etat == Feu::ARRET) {
                m->sender()->addMessage(new Message(this,Message::Arret));
                sleep(5);
                m_etat = Feu::PASSAGE;
                m->sender()->addMessage(new Message(this, Message::Passage));
            }
        }
        break;
        case Message::EstPasse:
        {
            sleep(1);
            m_etat = Feu::ARRET;
            m_free = false;
            if(m_syncLight != NULL) {
                Message * m1 = new Message(this, Message::Libre);
                m_syncLight->addMessage(m1);
            }
        }
        break;
        case Message::Libre:
        case Message::DoorClosed:
            {
                if(m_free){
                    m_etat = Feu::PASSAGE;
                }
                else
                {
                    m_free = true;
                }
            }
            break;
        }
    }
}

void FeuStation::setEtat(Feu::Etat etat) {
    this->m_etat = etat;
    if(etat == Feu::ARRET)
    {
        m_free = false;
    }
}
