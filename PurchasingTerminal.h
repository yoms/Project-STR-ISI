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

#ifndef PURCHASINGTERMINAL_H
#define PURCHASINGTERMINAL_H
#include "ThreadWithMessages.h"

/**
 * @brief Représente une borne d'achat.
 */
class PurchasingTerminal : public ThreadWithMessages
{
public:
    /**
     * @brief Représente une borne d'achat.
     */
    PurchasingTerminal();
    /**
     * @brief Detruit une borne d'achat.
     */
    virtual ~PurchasingTerminal();
    /**
     * @brief Représente le comportement d'une borne d'achat.
     */
    void run();
    /**
     * @brief Retourne le nom de la classe.
     * @return le nom de la classe
     */
    virtual QString className() {
        return QString("PurchasingTerminal");
    }
private:
    /**
     * @brief Donne un ticket.
     */
    void giveTicket();
private:
    void handleNewMessage();
    int id;
    static int globalId;
};

#endif // PURCHASINGTERMINAL_H
