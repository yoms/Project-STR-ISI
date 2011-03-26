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
#include <QPainter>
#include <QDebug>
#define SIZE_STATION 5
Station::Station():ThreadWithMessages(), Container()
{
    m_persons = new Person;
    m_persons->setContainer(this);
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

void Station::addStationLight(StationLight *f)
{
    m_stationLight = f;
}

void Station::run()
{

}

void Station::handleNewMessage()
{

    while(m_messageList.size())
    {
        Message* m = m_messageList.takeFirst();
        switch(m->type())
        {
            case Message::DoorsOpened:
            {
                startGetOnTheTram();
            }
            break;
            case Message::DoorsClosing:
            {
                stopGetOnTheTram();
            }
            break;
        }
        delete m;
    }
}

void Station::startGetOnTheTram()
{
    m_persons->addMessage(new Message(this,Message::DoorsOpened));
}

void Station::stopGetOnTheTram()
{
    m_persons->addMessage(new Message(this,Message::DoorsClosing));
}
