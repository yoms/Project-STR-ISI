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
        if(m_newMessage > 0) {
            qDebug()<<"m_newMessage "<<m_newMessage;
            if(m_etat == Feu::ARRET) {
                for(int i = (m_bal.size() - m_newMessage) ; i < m_bal.size() ; i++) {
                    pthread_kill(m_bal.at(i)->sender()->threadid(), SIGUSR1);
                }
            }
            m_newMessage = 0;
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
    for(int i = 0 ; i < m_bal.size() ; i++) {
        pthread_kill(m_bal.at(i)->sender()->threadid(), SIGUSR1);
    }
}

Feu::Etat Feu::etat() {
    return this->m_etat;
}
