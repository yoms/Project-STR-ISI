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

#include "Tram.h"
#include "Trip.h"
#include "Message.h"
#include "PunchingTerminal.h"

#include <QPainter>
#include <QDebug>
#define SIZE 3
#define SIZE_TRAM 4
#define VITESSE_MIN 40
#define VITESSE_MAX 5
#define ACCELERATION 3
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "Container.h"
#include "PunchingTerminal.h"

Tram::Tram():Drawable(),ThreadWithMessages(), Container()
{
    m_obstacle = NULL;
    m_punchingTerminal = NULL;
    m_state = Tram::Acceleration;
    m_nbTick = 0;
    m_velocity = VITESSE_MIN;
    pthread_mutex_init(&m_mutex,NULL);
    PunchingTerminal* m_punchingTerminal = new PunchingTerminal;
    m_punchingTerminal->start();
}
Tram::~Tram()
{
    delete m_punchingTerminal;
}
void Tram::run()
{
    for(;;)
    {
        pthread_mutex_lock(&m_mutex);
        obstacleTracking();
        if(m_nbTick == m_velocity-1)
        {
            this->m_nbTick = ++m_nbTick%m_velocity;
            switch(m_state)
            {
            case Tram::Acceleration:
                speedUp();
                move();
                break;
            case Tram::Desceleration:
                slowDown();
                if(m_obstacle != NULL)
                {
                    if(m_obstacle->place() == m_trip->next(m_coordinate))
                    {
                        m_velocity = VITESSE_MIN;
                        m_state = Tram::Off;
                    }
                    else
                        move();
                }
                break;
            case Tram::On:
                move();
                break;
            case Tram::Off:
                m_velocity = VITESSE_MIN;
                sendIsStoped();
                // check this.nbPerson et
                break;
            }
        }
    }
}
void Tram::obstacleTracking()
{
    Obstacle* o;
    if((o = m_trip->obstacleExist(this->m_coordinate)) != NULL)
    {
        m_obstacle = o;
        m_obstacle->addMessage(new Message(this,Message::TramToLightRequest));
    }
    else if(m_obstacle != NULL)
    {
        m_obstacle->addMessage(new Message(this,Message::IsCrossed));
        m_obstacle = NULL;
        m_state = Tram::Acceleration;
    }

}

void Tram::sendIsStoped()
{
    qDebug() << "tram stopped";
    if(m_obstacle != NULL)
    {
        Message* m = new Message(this,Message::IsStopped);
        m_obstacle->addMessage(m);
    }
}

void Tram::move()
{
    if(this->m_trip->next(this->m_coordinate) == m_coordinate)
        this->m_trip = this->m_trip->forward();
    this->m_coordinate = this->m_trip->next(this->m_coordinate);
}

void Tram::setTrip(Trip *t)
{
    this->m_trip=t;
    this->m_coordinate = this->m_trip->trip().first();
}

void Tram::tick()
{
   this->m_nbTick = ++m_nbTick%m_velocity;
   pthread_mutex_unlock(&m_mutex);
}

void Tram::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));
    QPoint buff = this->m_coordinate;
    for(int i = 0; i < SIZE; i++)
    {
        drawElemScen(painter, buff.x(), buff.y(), SIZE_TRAM);
        buff = this->m_trip->previous(buff);
    }
    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

void Tram::speedUp()
{
    if(m_velocity < VITESSE_MAX)
        m_state = Tram::On;
    else
        m_velocity -= ACCELERATION;
}

void Tram::slowDown()
{
    if(m_velocity >= VITESSE_MIN)
        m_state = Tram::Off;
    else
        m_velocity += ACCELERATION;
}

void Tram::openDoors()
{
    qDebug() << "ouverture des portes";
    //if(m_obstacle != NULL){}
}

void Tram::closeDoors()
{
    if(m_obstacle != NULL)
    {
        sleep(2);
        Message* m = new Message(this,Message::DoorsClosed);
        m_obstacle->addMessage(m);
    }
}

void Tram::handleNewMessage()
{
    while(!m_messageList.isEmpty())
    {
        Message *m = m_messageList.takeFirst();
        switch(m->type())
        {
        case Message::LightToTramStop:
            if(m_state != Tram::Off)
                m_state = Tram::Desceleration;
            break;
        case Message::LightToTramCross:
            m_state = Tram::Acceleration;
            break;
        case Message::WaitDoorClosed:
            if(m_state == Tram::Off)
                closeDoors();
            break;
        case Message::OpenDoors:
            qDebug() << "ouverture des portes";
            openDoors();
            break;
        }
        delete m;
    }
}

