#include "Feu.h"
#include <QPainter>
#include <QBrush>
#define SIZE_FEU 3
Feu::Feu():m_etat(Feu::PASSAGE)
{
    m_timer = new Timer(3);
    m_timer->addListener(this);
    m_timer->start();
}

void Feu::tick()
{
    this->m_etat = m_etat == Feu::ARRET ? Feu::PASSAGE : Feu::ARRET;
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
