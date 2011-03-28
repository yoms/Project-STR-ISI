/*
 *   Copyright 2011 by Alexandre Mendes <alex.mendes1988@gmail.com>
 *   Copyright 2011 by Bertrand Pages <pages.bertrand@gmail.com>
 *   Copyright 2011 by Guillaume Hormiere <hormiere.guillaume@gmail.com>
 *   Copyright 2011 by Nicolas Noullet <nicolas.noullet@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Trip.h"
#include <QPainter>
#define SIZE_POINT_TRAJET 2
Trip::Trip()
{
    pthread_mutex_init(&m_mutexTrip,NULL);
}
void Trip::draw(QPainter * painter)
{
    painter->save();
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::blue));

    for(int i = 0; i < m_trip.size(); i++)
    {
        drawElemScen(painter, m_trip[i].x(), m_trip[i].y(), SIZE_POINT_TRAJET);
    }

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

QList<QPoint> Trip::trip()
{
    QList<QPoint> retour = this->m_trip;
    return retour;
}

void Trip::setTrip(QList<QPoint> & lp)
{
    pthread_mutex_lock(&m_mutexTrip);
    this->m_trip = lp;
    pthread_mutex_unlock(&m_mutexTrip);
}
Obstacle* Trip::obstacleExist(QPoint monEmplacement, int distance)
{
    pthread_mutex_lock(&m_mutexTrip);
    int indexOf = m_trip.indexOf(monEmplacement);
    foreach(Obstacle* o, m_obstacle)
    {
        int j = 0;
        for(int i = 0; i < distance; i++)
        {
            QPoint oE;
            if(indexOf+i < m_trip.size())
                oE = m_trip.at(indexOf+i);
            else
            {
                pthread_mutex_unlock(&m_mutexTrip);
                return m_forwardTrip->obstacleExist(m_forwardTrip->trip().first(),DISTANCE_VISION-i);
            }
            if(o->place() == oE)
            {
                pthread_mutex_unlock(&m_mutexTrip);
                return o;
            }
        }
    }
    pthread_mutex_unlock(&m_mutexTrip);
    return NULL;
}
Obstacle* Trip::obstacleExist(QPoint monEmplacement)
{
    return obstacleExist(monEmplacement,DISTANCE_VISION);
}

void Trip::setObstacle(QList<Obstacle *> o)
{
    pthread_mutex_lock(&m_mutexTrip);
    m_obstacle = o;
    pthread_mutex_unlock(&m_mutexTrip);
}

void Trip::addObstacle(Obstacle *o)
{
    pthread_mutex_lock(&m_mutexTrip);
    m_obstacle << o;
    pthread_mutex_unlock(&m_mutexTrip);
}

QPoint Trip::next(QPoint p)
{
      return m_trip.indexOf(p)+1 < m_trip.size() ? m_trip[m_trip.indexOf(p)+1] : m_trip[m_trip.indexOf(p)];
}

QPoint Trip::previous(QPoint p)
{
    return m_trip.indexOf(p)-1 >= 0 ? m_trip.at(m_trip.indexOf(p)-1) : m_trip.at(m_trip.indexOf(p));
}
