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

#include "Light.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
#define SIZE_LIGHT 3
Light::Light():m_state(Light::Green),m_previousLight(NULL)
{
}

void Light::draw(QPainter * painter)
{
    painter->save();
    switch(this->m_state)
    {
    case Light::Red:
        {
            painter->setPen(Qt::red);
            painter->setBrush(QBrush(Qt::red));
        }
    break;
    case Light::Green:
        {
            painter->setPen(Qt::green);
            painter->setBrush(QBrush(Qt::green));
        }
    break;
    }
    drawElemScen(painter, m_coordinate.x(), m_coordinate.y(), SIZE_LIGHT);

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

void Light::run()
{
    for(;;)
    {
        sleep(1);
    }
}
void Light::handleNewMessage()
{

    while(m_messageList.size())
    {
        Message* m = m_messageList.takeFirst();
        switch(m->type())
        {
            case Message::Request:
            {
                if(m_state == Light::Red) {
                    m->sender()->addMessage(new Message(this,Message::Stop));
                }
                else if(m_state == Light::Green) {
                    m->sender()->addMessage(new Message(this,Message::Cross));
                }
            }
            break;
            case Message::IsCrossed:
            {
                sleep(1);
                m_state = Light::Red;
                if(m_previousLight != NULL) {
                    Message * m1 = new Message(this, Message::IsFree);
                    m_previousLight->addMessage(m1);
                }
            }
            break;
        case Message::IsFree:
            {
                m_state = Light::Green;
            }
            break;
        }
    }
}

bool Light::indicateState() {
    switch(this->m_state)
    {
    case Light::Red:
        return false;
    case Light::Green:
        return true;
    }
}

void Light::setColor(Light::Color state) {
    this->m_state = state;
}

Light::Color Light::state() {
    return this->m_state;
}

void Light::setPreviousLight(Light * f) {
    m_previousLight = f;
}