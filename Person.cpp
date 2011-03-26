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

Person::Person():ThreadWithMessages(),m_container(NULL), m_state(Person::NeedGetOnTheTram), m_nbPerson(5)
{

}
Person::~Person()
{

}

void Person::run()
{

}
void Person::buyTicket()
{
    //appeler m_nbPerson fois purchaseTicket
    //ajouter : m_state == Person::NeedGetOnTheTram;

}

void Person::punchTicket()
{
    //appeler m_nbPerson fois punchTicket
    //ajouter : m_state == Person::NeedGetOffTheTram;
}

void Person::getOnTheTram(Container* tram)
{
    this->m_container->quit(this);
    this->m_container = tram;
    this->m_container->enter(this);
    // A remplacer par : m_state == Person::NeedPunchTicket;
    m_state == Person::NeedGetOffTheTram;
    // A ajouter : this->punchTicket();
}

void Person::getOffTheTram(Container* station)
{
    this->m_container->quit(this);
    this->m_container = station;
    this->m_container->enter(this);
    // A remplacer par : m_state == Person::NeedTicket;
    m_state == Person::NeedGetOnTheTram;
    // A ajouter : this->buyTicket();
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
            case Message::TramIncoming:
                if(m_state == Person::NeedGetOnTheTram)
                    getOnTheTram((Container*)m->sender());
            case Message::ReachingStation:
                if(m_state == Person::NeedGetOffTheTram)
                    getOffTheTram((Container*)m->sender());
        }
        delete m;
    }
}
