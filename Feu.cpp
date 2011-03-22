#include "Feu.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
#define SIZE_FEU 3
Feu::Feu():m_etat(Feu::PASSAGE)
{
}

void Feu::draw(QPainter * painter)
{
    painter->save();
    switch(this->m_etat)
    {
    case Feu::ARRET:
        {
            painter->setPen(Qt::red);
            painter->setBrush(QBrush(Qt::red));
        }
    break;
    case Feu::PASSAGE:
        {
            painter->setPen(Qt::green);
            painter->setBrush(QBrush(Qt::green));
        }
    break;
    }
    drawElemScen(painter, m_coordonnee.x(), m_coordonnee.y(), SIZE_FEU);

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

void Feu::run()
{
    for(;;)
    {
        sleep(1);
    }
}
void Feu::newMessage()
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
        m_etat = Feu::ARRET;
    }
    }
}

bool Feu::indiquerPassage() {
    switch(this->m_etat)
    {
    case Feu::ARRET:
        return false;
    case Feu::PASSAGE:
        return true;
    }
}

void Feu::setEtat(Feu::Etat etat) {
    this->m_etat = etat;
}

Feu::Etat Feu::etat() {
    return this->m_etat;
}
