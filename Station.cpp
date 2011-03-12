#include "Station.h"
#include <QPainter>
#include <QDebug>
#define SIZE_STATION 5
Station::Station(Station::Type t):m_typeStation(t)
{
}
void Station::draw(QPainter *painter)
{
    painter->save();
    if(m_typeStation == Station::Terminus)
    {
        painter->setPen(Qt::green);
        painter->setBrush(QBrush(Qt::green));
    }
    else
    {
        painter->setPen(Qt::yellow);
        painter->setBrush(QBrush(Qt::yellow));
    }

    drawElemScen(painter, m_coordonnee.x(), m_coordonnee.y(), SIZE_STATION);

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

bool Station::indiquerPassage()
{
    switch(this->m_typeStation)
    {
    case Station::Terminus:
        return false;
    case Station::NonTerminus:
        switch(this->m_feuStation->etat())
        {
        case Feu::ARRET:
            return false;
        case Feu::PASSAGE:
            return true;
        }
    }
}


void Station::addFeuStation(FeuStation *f)
{
    m_feuStation = f;
}
