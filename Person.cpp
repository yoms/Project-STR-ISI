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

#include "Person.h"

Person::Person():ThreadWithMessages(),m_nbPersonsWithTicket(0),m_nbPersonsWithPunchedTicket(0),m_container(NULL)
{
    int nb = (int)threadid() % 120 + 80;
    m_nbPersonsWithoutTicket = nb;
}
Person::~Person()
{

}

void Person::run()
{

}
void Person::buyTicket()
{
    m_nbPersonsWithTicket++;
    m_nbPersonsWithoutTicket--;
    //appel ada
}

void Person::punchTicket()
{
    m_nbPersonsWithPunchedTicket++;
    m_nbPersonsWithTicket--;
    //appel ada
}

void Person::getOnTheTram()
{
    // tant que le tram n'est pas plein et qu'il reste des passagers dans la station
}

void Person::getOffTheTram()
{
}

void Person::waitInStation()
{
}

void Person::waitInTram()
{
}

void Person::triggerEmergencyStop()
{
}

void Person::handleNewMessage()
{

    while(m_messageList.size())
    {
        Message* m = m_messageList.takeFirst();
        switch(m->type())
        {
            case Message::DoorsOpened:
            {
            }
            break;
            case Message::DoorsClosed:
            case Message::DoorsClosing:
            {
            }
            break;
        }
        delete m;
    }
}
