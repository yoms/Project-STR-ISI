#include "Station.h"
#include <QPainter>
#define SIZE_STATION 5
Station::Station(Station::Type t):typeStation(t)
{
}
void Station::draw(QPainter *painter)
{
    painter->save();
    if(typeStation == Station::Terminus)
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
