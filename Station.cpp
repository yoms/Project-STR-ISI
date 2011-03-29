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

#include "Station.h"
#include "Container.h"
#include "PurchasingTerminal.h"
#include <QPainter>
#include <QDebug>
#define SIZE_STATION 5
Station::Station():Container()
{
    m_purchasingTerminal = new PurchasingTerminal;
    m_purchasingTerminal->start();
}
Station::~Station()
{
    delete m_purchasingTerminal;
}
void Station::draw(QPainter *painter)
{
    painter->save();

    painter->setPen(Qt::yellow);
    painter->setBrush(QBrush(Qt::yellow));

    drawElemScen(painter, m_coordinate.x(), m_coordinate.y(), SIZE_STATION);

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

void Station::run()
{
    for(;;)
    {
        // le sleep est arrété lorsqu'un nouveau message apparait
        sleep(1);
    }
}
void Station::addStationLight(StationLight *f)
{
    m_stationLight = f;
}
void Station::handleNewMessage()
{
    while(!m_messageList.isEmpty())
    {
        Message *m = m_messageList.takeFirst();
        switch(m->type())
        {
        case Message::EnterStation:
            this->enter((Person*)m->sender());
            break;
        case Message::QuitStation:
            this->quit((Person*)m->sender());
            break;
        default:
            break;
        }
        delete m;
    }
}
