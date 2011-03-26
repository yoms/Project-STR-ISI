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
    QList<QPoint> retour = this->m_trip;
    return retour;
}

void Trip::setTrip(QList<QPoint> & lp)
{
    pthread_mutex_lock(&m_mutex);
    this->m_trip = lp;
    pthread_mutex_unlock(&m_mutex);
}
Obstacle* Trip::obstacleExist(QPoint monEmplacement)
{
    pthread_mutex_lock(&m_mutex);
    foreach(Obstacle* o, m_obstacle)
    {
        int j = 0;
        for(int i = 0; i < DISTANCE_VISION; i++)
        {
            QPoint oE;
            if(m_trip.indexOf(monEmplacement)+i < m_trip.size())
                oE = m_trip[m_trip.indexOf(monEmplacement)+i];
            else
            {
                if(j < m_forwardTrip->trip().size())
                    oE = m_forwardTrip->trip()[j++];
            }
            if(o->place() == oE)
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
    pthread_mutex_lock(&m_mutex);
    m_obstacle = o;
    pthread_mutex_unlock(&m_mutex);
}

void Trip::addObstacle(Obstacle *o)
{
    pthread_mutex_lock(&m_mutex);
    m_obstacle << o;
    pthread_mutex_unlock(&m_mutex);
}

QPoint Trip::next(QPoint p)
{
    pthread_mutex_lock(&m_mutex);
    QPoint retour = m_trip.indexOf(p)+1 < m_trip.size() ? m_trip[m_trip.indexOf(p)+1] : m_trip[m_trip.indexOf(p)];
    pthread_mutex_unlock(&m_mutex);
    return retour;
}

QPoint Trip::previous(QPoint p)
{
    pthread_mutex_lock(&m_mutex);
    QPoint retour = m_trip.indexOf(p)-1 >= 0 ? m_trip.at(m_trip.indexOf(p)-1) : m_trip.at(m_trip.indexOf(p));
    pthread_mutex_unlock(&m_mutex);
    return retour;
}
