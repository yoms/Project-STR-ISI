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
#include "Tram.h"
#include "Station.h"
#include "PurchasingTerminal.h"
#include "PunchingTerminal.h"
#include <QDebug>

Person::Person(Person::State s): ThreadWithMessages(), m_nbPerson(5)
{
    m_container = NULL;
    m_state = s;
    m_nbTicketToBuy = 0;
    m_nbTicketToPunch = 0;
}
Person::~Person()
{}

void Person::run()
{
    for(;;)
        sleep(1);
}
void Person::buyTicket(PurchasingTerminal * purchasingTerm)
{
    for(int i = 0; i < m_nbPerson; i++)
        purchasingTerm->addMessage(new Message(this, Message::BuyTicket));
    m_nbTicketToBuy += m_nbPerson;
}

void Person::punchTicket(PunchingTerminal * punchingTerm)
{
    for(int i = 0; i < m_nbPerson; i++)
        punchingTerm->addMessage(new Message(this, Message::PunchTicket));
    m_nbTicketToPunch += m_nbPerson;
}

void Person::getOnTheTram(Tram* tram)
{
    qDebug() << "------" << m_nbPerson << "personnes montent dans le tram";
    m_container->addMessage(new Message(this, Message::QuitStation));
    this->m_container = tram;
    tram->addMessage(new Message(this, Message::EnterTram));
    m_state = Person::NeedPunchTicket;
    punchTicket(tram->punchingTerminal());
}

void Person::getOffTheTram(Station* station)
{
    qDebug() << "------" << m_nbPerson << "personnes descendent du tram";
    m_container->addMessage(new Message(this, Message::QuitTram));
    this->m_container = station;
    station->addMessage(new Message(this, Message::EnterStation));
    m_state = Person::NeedTicket;
    buyTicket(station->purchasingTerminal());
}

void Person::triggerEmergencyStop()
{
}

void Person::handleNewMessage()
{
    while(m_messageList.size()) {
        Message* m = m_messageList.takeFirst();
        switch(m->type()) {
        case Message::TramIncoming:
            if(m_state == Person::NeedGetOnTheTram)
                getOnTheTram((Tram*)m->sender());
            break;
        case Message::ReachingStation:
            if(m_state == Person::NeedGetOffTheTram)
                getOffTheTram((Station*)m->sender());
            break;
        case Message::TicketBought:
            m_nbTicketToBuy --;
            if(m_nbTicketToBuy == 0) {
                m_state = Person::NeedGetOnTheTram;
                qDebug() << "------" << m_nbPerson << "personnes ont achete leur ticket";
            }
            break;
        case Message::TicketPunched:
            m_nbTicketToPunch --;
            if(m_nbTicketToPunch == 0) {
                m_state = Person::NeedGetOffTheTram;
                qDebug() << "------" << m_nbPerson << "personnes ont composte leur ticket";
            }
            break;
        default:
            break;
        }
        delete m;
    }
}

QList<Person*> Person::personsReadyToGetOn(QList<Person*> all)
{
    QList<Person*> personsReady;
    for(int i = 0 ; i < all.size() ; i++)
        if(all.at(i)->getState() == Person::NeedGetOnTheTram)
            personsReady.append(all.at(i));
    return personsReady;
}

QList<Person*> Person::personsReadyToGetOff(QList<Person*> all)
{
    QList<Person*> personsReady;
    for(int i = 0 ; i < all.size() ; i++)
        if(all.at(i)->getState() == Person::NeedGetOffTheTram)
            personsReady.append(all.at(i));
    return personsReady;
}
