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

Tram::Tram():Drawable(), Container()
        , m_punchingTerminal(new PunchingTerminal)
        ,  m_velocity(VITESSE_MIN)
{
    m_obstacle = NULL;
    m_nbTick = 0;
    m_state = Tram::Acceleration;
    pthread_mutex_init(&m_mutexTram,NULL);
    m_security = 0;
    m_generateProblem = false;
    m_problemDetected = false;
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
        pthread_mutex_lock(&m_mutexTram);

        if( this->m_generateProblem  && !m_problemDetected)
        {
            m_problemDetected = true;
        }
        obstacleTracking();
        if(m_nbTick == m_velocity-1)
        {
            this->m_nbTick = ++m_nbTick%m_velocity;
            switch(m_state)
            {
            case Tram::Acceleration:
                if(m_problemDetected )
                {
                    if(m_security < 8 && m_obstacle == NULL)
                        m_security++;
                    else
                    {
                        m_state = Tram::Desceleration;
                        m_security = 0;
                    }
                }
                speedUp();
                move();
                break;
            case Tram::OutOfOrder:
                break;
            case Tram::Desceleration:
                slowDown();
                if(m_obstacle != NULL)
                {
                    if(m_obstacle->place() == m_trip->next(m_coordinate))
                    {
                        m_velocity = VITESSE_MIN;
                        m_state = Tram::Off;
                        sendIsStoped();
                    }
                    else
                        move();
                }
                break;
            case Tram::On:
                if(m_problemDetected)
                {
                    if(m_security < 8 && m_obstacle == NULL)
                        m_security++;
                    else
                    {
                        m_state = Tram::Desceleration;
                        m_security = 0;
                    }
                }
                move();
                break;
            case Tram::Off:
                m_velocity = VITESSE_MIN;
                // check this.nbPerson et
                sendIsStoped();
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
        m_security++;
    }

}

void Tram::sendIsStoped()
{
    qDebug() << "Arret du tram";
    m_security = 0;
    if(!m_problemDetected)
    {
        if(m_obstacle != NULL)
        {
            Message* m = new Message(this,Message::IsStopped);
            m_obstacle->addMessage(m);
        }
    }
    else
    {
        m_state = Tram::OutOfOrder;
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
    srand ( time(NULL) );
    int panne = (rand()+this->m_nbTick+10000) % 1000;
    int panne2 = (this->velocity()+this->threadid()+1) % 1000;
    this->m_generateProblem = (panne == panne2);
    this->m_nbTick = ++m_nbTick%m_velocity;
    pthread_mutex_unlock(&m_mutexTram);
}

void Tram::draw(QPainter *painter)
{
    painter->save();
    QPoint buff;
    if(isSelect())
    {
        buff = this->m_coordinate;
        for(int i = 0; i < SIZE; i++)
        {
            painter->setPen(Qt::yellow);
            painter->setBrush(QBrush(Qt::yellow));
            drawElemScen(painter, buff.x()-1, buff.y()-1, SIZE_TRAM+2);
            buff = this->m_trip->previous(buff);
        }
    }

    buff = this->m_coordinate;
    for(int i = 0; i < SIZE; i++)
    {
        if(m_problemDetected)
        {
            painter->setPen(QColor(255, 165, 0));
            painter->setBrush(QBrush(QColor(255, 165, 0)));
        }
        else
        {
            painter->setPen(Qt::red);
            painter->setBrush(QBrush(Qt::red));
        }
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

void Tram::manageStationStop()
{
    qDebug() << "ouverture des portes";
    StationLight * stationLight = (StationLight *) m_obstacle;
    qDebug() << "--les passagers descendent";
    for(int i = 0 ; i < persons().size() ; i++)
    {
        Message * m = new Message(stationLight->station(), Message::ReachingStation);
        persons().at(i)->addMessage(m);
    }
    qDebug() << "--les passagers montent";
    QList<Person*> stationPersons = stationLight->station()->persons();
    for(int i = 0 ; i < stationPersons.size() ; i++)
    {
        Message * m = new Message(this, Message::TramIncoming);
        stationPersons.at(i)->addMessage(m);
    }
    if(! m_problemDetected)
    {
        qDebug() << "fermeture des portes";
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
            if(m_state != Tram::Off && m_state != OutOfOrder)
                m_state = Tram::Desceleration;
            break;
        case Message::Solved:
            m_problemDetected = false;
            m_generateProblem = false;
        case Message::LightToTramCross:
            m_state = Tram::Acceleration;
            break;
        case Message::ManageStationStop:
            manageStationStop();
            break;
        case Message::EnterTram:
            this->enter((Person*)m->sender());
            break;
        case Message::QuitTram:
            this->quit((Person*)m->sender());
            break;
        default:
            break;
        }
        delete m;
    }
}

