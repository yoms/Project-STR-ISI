#include "Trajet.h"
#include <QPainter>
#define SIZE_POINT_TRAJET 2
Trajet::Trajet()
{
}
void Trajet::draw(QPainter * painter)
{
    painter->save();
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::blue));

    foreach(QPoint p, m_trajet)
    {
        drawElemScen(painter, p.x(), p.y(), SIZE_POINT_TRAJET);
    }


    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

QList<QPoint> Trajet::trajet()
{
    return this->m_trajet;
}

void Trajet::setTrajet(QList<QPoint> & lp)
{
    this->m_trajet = lp;
}

QPoint Trajet::next(QPoint& p)
{
    return m_trajet.indexOf(p)+1 < m_trajet.size() ? m_trajet[m_trajet.indexOf(p)+1] : m_trajet[m_trajet.indexOf(p)];
}

QPoint Trajet::previous(QPoint& p)
{
    return m_trajet.indexOf(p)-1 >= 0 ? m_trajet[m_trajet.indexOf(p)-1] : m_trajet[m_trajet.indexOf(p)];
}
