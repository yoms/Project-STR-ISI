#include "Trajet.h"
#include <QPainter>
#define SIZE_POINT_TRAJET 2
#define DISTANCE_VISION 10
Trajet::Trajet()
{
    pthread_mutex_init(&m_mutex,NULL);
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
Obstacle* Trajet::obstacleExist(QPoint monEmplacement)
{

    pthread_mutex_lock(&m_mutex);
    foreach(Obstacle* o, m_obstacle)
    {
        for(int i = 0; i < DISTANCE_VISION; i++)
        {

            int indexof = m_trajet.indexOf(monEmplacement)+i < m_trajet.size()
                                ? m_trajet.indexOf(monEmplacement)+i
                                : m_trajet.indexOf(monEmplacement);
            if(o->lieu() == m_trajet[indexof])
            {
                pthread_mutex_unlock(&m_mutex);
                return o;
            }
        }
    }
    pthread_mutex_unlock(&m_mutex);
    return NULL;
}

void Trajet::setObstacle(QList<Obstacle *> o)
{
    m_obstacle = o;
}

void Trajet::addObstacle(Obstacle *o)
{
    m_obstacle << o;
}

QPoint Trajet::next(QPoint& p)
{
    return m_trajet.indexOf(p)+1 < m_trajet.size() ? m_trajet[m_trajet.indexOf(p)+1] : m_trajet[m_trajet.indexOf(p)];
}

QPoint Trajet::previous(QPoint& p)
{
    return m_trajet.indexOf(p)-1 >= 0 ? m_trajet[m_trajet.indexOf(p)-1] : m_trajet[m_trajet.indexOf(p)];
}
