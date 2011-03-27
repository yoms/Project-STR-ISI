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
#include "PurchasingTerminal.h"
#include "PunchingTerminal.h"
#include <QDebug>

Person::Person():ThreadWithMessages(),m_container(NULL), m_state(Person::NeedGetOnTheTram), m_nbPerson(5)
{}
Person::~Person()
{}

void Person::run()
{
    for(;;)
        sleep(1);
}
void Person::buyTicket(PurchasingTerminal * purchasingTerm)
{
    for(int i=0; i<m_nbPerson; i++)
        purchasingTerm->giveTicket();
    m_state == Person::NeedGetOnTheTram;
}

void Person::punchTicket(PunchingTerminal * punchingTerm)
{
    for(int i=0; i<m_nbPerson; i++)
        punchingTerm->punchTicket();
    m_state == Person::NeedGetOffTheTram;
}

void Person::getOnTheTram(Container* tram)
{
    qDebug() << "Personne passe de station a tram";
    this->m_container->quit(this);
    this->m_container = tram;
    ((ThreadWithMessages*) tram)->addMessage(new Message(this, Message::EnterTram));
    m_state == Person::NeedGetOffTheTram;     // A remplacer par : m_state == Person::NeedPunchTicket;
    // A ajouter : this->punchTicket();
}

void Person::getOffTheTram(Container* station)
{
    qDebug() << "Personne passe de tram a station";
    ThreadWithMessages* tram = (ThreadWithMessages*)this->m_container;
    tram->addMessage(new Message(this, Message::QuitTram));
    this->m_container = station;
    this->m_container->enter(this);
    m_state == Person::NeedGetOnTheTram;     // A remplacer par : m_state == Person::NeedTicket;
    // A ajouter : this->buyTicket();
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
            break;
        case Message::ReachingStation:
            if(m_state == Person::NeedGetOffTheTram)
                getOffTheTram((Container*)m->content());
            break;
        }
        delete m;
    }
}
