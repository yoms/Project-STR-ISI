#include "Station.h"
#include <QPainter>
#define SIZE_STATION 5
Station::Station(Station::Type t):typeStation(t)
{
}
void Station::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::blue));

    drawElemScen(painter, m_coordonnee.x(), m_coordonnee.y(), SIZE_STATION);

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}
