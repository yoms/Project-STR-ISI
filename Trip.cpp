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
    pthread_mutex_init(&m_mutex,NULL);
}
void Trip::draw(QPainter * painter)
{
    painter->save();
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::blue));

    foreach(QPoint p, m_trip)
    {
        drawElemScen(painter, p.x(), p.y(), SIZE_POINT_TRAJET);
    }

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

QList<QPoint> Trip::trip()
{
    return this->m_trip;
}

void Trip::setTrip(QList<QPoint> & lp)
{
    this->m_trip = lp;
}
Obstacle* Trip::obstacleExist(QPoint monEmplacement)
{
    pthread_mutex_lock(&m_mutex);
    foreach(Obstacle* o, m_obstacle)
    {
        for(int i = 0; i < DISTANCE_VISION; i++)
        {
            int indexof = m_trip.indexOf(monEmplacement)+i < m_trip.size()
                                ? m_trip.indexOf(monEmplacement)+i
                                : m_trip.indexOf(monEmplacement);
            if(o->place() == m_trip[indexof])
            {
                pthread_mutex_unlock(&m_mutex);
                return o;
            }
        }
    }
    pthread_mutex_unlock(&m_mutex);
    return NULL;
}

void Trip::setObstacle(QList<Obstacle *> o)
{
    m_obstacle = o;
}

void Trip::addObstacle(Obstacle *o)
{
    m_obstacle << o;
}

QPoint Trip::next(QPoint& p)
{
    return m_trip.indexOf(p)+1 < m_trip.size() ? m_trip[m_trip.indexOf(p)+1] : m_trip[m_trip.indexOf(p)];
}

QPoint Trip::previous(QPoint& p)
{
    return m_trip.indexOf(p)-1 >= 0 ? m_trip[m_trip.indexOf(p)-1] : m_trip[m_trip.indexOf(p)];
}
