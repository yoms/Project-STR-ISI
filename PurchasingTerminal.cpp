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

#include "PurchasingTerminal.h"
#include <QDebug>

pthread_mutex_t mutexGlobalPurchaseId = PTHREAD_MUTEX_INITIALIZER;

extern "C" {
    void adaPurchaseTicket(int);
}

int PurchasingTerminal::globalId = 0;

PurchasingTerminal::PurchasingTerminal(): ThreadWithMessages()
{
    pthread_mutex_lock(&mutexGlobalPurchaseId);
    globalId ++;
    Q_ASSERT(globalId < 10);
    this->id = globalId;
    pthread_mutex_unlock(&mutexGlobalPurchaseId);
}

PurchasingTerminal::~PurchasingTerminal() {}

void PurchasingTerminal::run()
{
    for(;;)
        sleep(1);
}

void PurchasingTerminal::giveTicket()
{
    adaPurchaseTicket(this->id);
}

void PurchasingTerminal::handleNewMessage()
{
    while(!m_messageList.isEmpty()) {
        Message *m = m_messageList.takeFirst();
        switch(m->type()) {
        case Message::BuyTicket:
            this->giveTicket();
            m->sender()->addMessage(new Message(this, Message::TicketBought));
            break;
        default:
            break;
        }
        delete m;
    }
}
