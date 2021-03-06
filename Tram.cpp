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
#include "StationLight.h"
#include <QPainter>
#include <QDebug>
#define SIZE 5
#define SIZE_TRAM 4
#define VITESSE_MIN 40
#define VITESSE_MAX 5
#define ACCELERATION 3
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "Container.h"
#include "PunchingTerminal.h"

Tram::Tram(): Drawable(), Container()
    , m_punchingTerminal(new PunchingTerminal)
    ,  m_velocity(VITESSE_MIN)
    , m_nbPeopleGettingOff(0)
    , m_nbPeopleGettingOn(0)
{
    m_obstacle = NULL;
    m_nbTick = 0;
    m_state = Tram::Acceleration;
    pthread_mutex_init(&m_mutexTram, NULL);
    m_punchingTerminal->start();
    m_beforeOutOfOrder = Tram::OutOfOrder;
    m_generateProblem = false;
    for(int i = 0 ; i < NB_DOORS ; i++) {
        Door d;
        m_doors.append(d);
    }
}
Tram::~Tram()
{
    delete m_punchingTerminal;
}
void Tram::run()
{
    for(;;) {
        pthread_mutex_lock(&m_mutexTram);
        if(m_state != Tram::OutOfOrder)
            obstacleTracking();
        if(m_nbTick == m_velocity - 1) {
            this->m_nbTick = ++m_nbTick % m_velocity;
            switch(m_state) {
            case Tram::Acceleration:
                speedUp();
                move();
                break;
            case Tram::OutOfOrder:
                m_velocity = VITESSE_MIN;
                break;
            case Tram::Desceleration:
                slowDown();
                if(m_obstacle != NULL) {
                    if(m_obstacle->place() == m_trip->next(m_coordinate)) {
                        m_velocity = VITESSE_MIN;
                        m_state = Tram::Off;
                        sendIsStoped();
                    } else
                        move();
                }
                break;
            case Tram::On:
                move();
                break;
            case Tram::Off:
                m_velocity = VITESSE_MIN;
                break;
            }
        }
    }
}
void Tram::obstacleTracking()
{
    Obstacle* o;
    if((o = m_trip->obstacleExist(this->m_coordinate)) != NULL) {
        m_obstacle = o;
        m_obstacle->addMessage(new Message(this, Message::TramToLightRequest));
    } else if(m_obstacle != NULL) {
        m_state = Tram::Acceleration;
        bool isCrossed = false;
        QPoint p = m_trip->previous(m_coordinate);
        int i = 0;
        int nbCase = SIZE + SIZE_LIGHT + 1;
        for(i = 0; i < nbCase && m_obstacle->place() != p; i++) {
            p = m_trip->previous(p);
        }
        isCrossed = i == nbCase - 1;
        if(isCrossed) {
            m_obstacle->addMessage(new Message(this, Message::IsCrossed));
            m_obstacle = NULL;
        }
    }

}

void Tram::sendIsStoped()
{
    if(m_obstacle != NULL) {
        qDebug() << "arret de" << name();
        Message* m = new Message(this, Message::IsStopped);
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
    this->m_trip = t;
    this->m_coordinate = this->m_trip->trip().first();
}

void Tram::tick()
{
    srand(time(NULL));
    if(m_state != Tram::OutOfOrder && m_generateProblem) {
        int panne = (rand() + this->m_nbTick + 10000) % 1000;
        int panne2 = (this->velocity() + this->threadid() + 1) % 1000;
        if(panne == panne2) {
            this->m_beforeOutOfOrder = m_state;
            this->m_state = Tram::OutOfOrder;
        }
    }
    this->m_nbTick = ++m_nbTick % m_velocity;
    pthread_mutex_unlock(&m_mutexTram);
}

void Tram::draw(QPainter *painter)
{
    painter->save();
    QPoint buff;
    if(isSelect()) {
        buff = this->m_coordinate;
        for(int i = 0; i < SIZE; i++) {
            painter->setPen(Qt::yellow);
            painter->setBrush(QBrush(Qt::yellow));
            drawElemScen(painter, buff.x() - 1, buff.y() - 1, SIZE_TRAM + 2);
            buff = this->m_trip->previous(buff);
        }
    }

    buff = this->m_coordinate;
    for(int i = 0; i < SIZE; i++) {
        if(m_state == Tram::OutOfOrder) {
            painter->setPen(QColor(255, 165, 0));
            painter->setBrush(QBrush(QColor(255, 165, 0)));
        } else {
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
    /*
       if(m_velocity >= VITESSE_MIN)
           m_state = Tram::Off;*/
    if(m_velocity < VITESSE_MIN)
        m_velocity += ACCELERATION;
}

void Tram::openDoors()
{
    qDebug() << "ouverture de" << NB_DOORS << "portes";
    for(int i = 0 ; i < NB_DOORS ; i++) {
        m_doors[i].open();
    }
    makePeopleGetOff();
}

void Tram::makePeopleGetOff()
{
    StationLight * stationLight = (StationLight *) m_obstacle;
    QList<Person*> personsReadyToGetOff = Person::personsReadyToGetOff(persons());
    m_nbPeopleGettingOff = personsReadyToGetOff.size();
    if(m_nbPeopleGettingOff > 0) {
        qDebug() << "----les passagers descendent";
        for(int i = 0 ; i < m_nbPeopleGettingOff ; i++) {
            Message * m = new Message(stationLight->station(), Message::ReachingStation);
            personsReadyToGetOff.at(i)->addMessage(m);
        }
    } else
        makePeopleGetOn();
}

void Tram::makePeopleGetOn()
{
    // Permet de visualiser l'arrêt dans l'IHM
    sleep(2);
    StationLight * stationLight = (StationLight *) m_obstacle;
    QList<Person*> stationPersons = stationLight->station()->persons();
    QList<Person*> personsReadyToGetOn = Person::personsReadyToGetOn(stationPersons);
    m_nbPeopleGettingOn = personsReadyToGetOn.size();
    if(m_nbPeopleGettingOn > 0) {
        qDebug() << "----les passagers montent";
        for(int i = 0 ; i < m_nbPeopleGettingOn ; i++) {
            Message * m = new Message(this, Message::TramIncoming);
            personsReadyToGetOn.at(i)->addMessage(m);
        }
    } else
        closeDoors();
}

void Tram::closeDoors()
{
    qDebug() << "fermeture de" << NB_DOORS << "portes";
    for(int i = 0 ; i < NB_DOORS ; i++) {
        m_doors[i].close();
    }
    Message* m = new Message(this, Message::DoorsClosed);
    m_obstacle->addMessage(m);
}

void Tram::restartAfterOutOfOrder()
{
    if(m_state == Tram::OutOfOrder) {
        this->m_state = this->m_beforeOutOfOrder;
        if(m_state == Tram::On)
            this->m_state = Tram::Acceleration;
    }

}

void Tram::handleNewMessage()
{
    while(!m_messageList.isEmpty()) {
        Message *m = m_messageList.takeFirst();
        switch(m->type()) {
        case Message::LightToTramStop:
            if(m_state != Tram::Off)
                m_state = Tram::Desceleration;
            break;
        case Message::LightToTramCross:
            if(m_state == Tram::Off)
                qDebug() << "depart de" << name();
            m_state = Tram::Acceleration;
            break;
        case Message::ManageStationStop:
            openDoors();
            break;
        case Message::EnterTram:
            enter((Person*)m->sender());
            m_nbPeopleGettingOn --;
            if(m_nbPeopleGettingOn == 0)
                closeDoors();
            break;
        case Message::QuitTram:
            quit((Person*)m->sender());
            m_nbPeopleGettingOff --;
            if(m_nbPeopleGettingOff == 0)
                makePeopleGetOn();
            break;
        case Message::Solved:
            restartAfterOutOfOrder();
            break;
        case Message::ProblemDetected:
            if(m_state != Tram::OutOfOrder) {
                this->m_beforeOutOfOrder = this->m_state;
                this->m_state = Tram::OutOfOrder;
            }
            break;
        default:
            break;
        }
        delete m;
    }
}

