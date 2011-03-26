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

#include "StationLight.h"
#include <QDebug>

StationLight::StationLight():m_free(true),m_doorClosed(true)
{
}

void StationLight::addStation(Station* s){
    m_station = s;
}

void StationLight::handleNewMessage(){
    while(m_messageList.size())
    {
        Message* m = m_messageList.takeFirst();
        switch(m->type()){
        case Message::Request:
        {
            if(m_state == Light::Red) {
                m->sender()->addMessage(new Message(this,Message::Stop));
                m->sender()->addMessage(new Message(this, Message::WaitDoorClosed));
            }
            if(m_state == Light::Green){
                m->sender()->addMessage(new Message(this,Message::Cross));
            }
        }
        break;
        case Message::IsCrossed:
        {
            sleep(1);
            qDebug() << this->name() << " isCrossed";
            m_state = Light::Red;
            m_free = false;
            m_doorClosed = false;
            if(m_previousLight != NULL) {
                Message * m1 = new Message(this, Message::IsFree);
                m_previousLight->addMessage(m1);
            }
        }
        break;
        case Message::IsFree:
            {
                m_free = true;
                if(m_doorClosed && m_free)
                {
                    m_state = Light::Green;
                    m->sender()->addMessage(new Message(this,Message::Cross));
                }
            }
        break;
        case Message::DoorsClosed:
            {
                m_doorClosed = true;
                if(m_free && m_doorClosed)
                {
                    m_state = Light::Green;
                    m->sender()->addMessage(new Message(this,Message::Cross));
                }
            }
        break;
        case Message::IsStopped:
            {
                m->sender()->addMessage(new Message(this,Message::OpenDoors));
            }
        break;
        case Message::DoorsOpened:
            {
                m_station->addMessage(new Message(this, Message::DoorsOpened));
            }
        break;
        }
        delete m;
    }
}

void StationLight::setColor(Light::Color etat) {
    this->m_state = etat;
    if(etat == Light::Red)
    {
        m_free = false;
        m_doorClosed = false;
    }
}
