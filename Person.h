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

#ifndef PERSON_H
#define PERSON_H
#include "ThreadWithMessages.h"
#include "Tram.h"
#include "Station.h"
#include <QString>
class Container;
class PurchasingTerminal;
class PunchingTerminal;

/**
 * @brief Représente un groupe de passagers.
 */
class Person : public ThreadWithMessages
{
public:
    enum State{
        NeedTicket,
        NeedGetOnTheTram,
        NeedPunchTicket,
        NeedGetOffTheTram
    };
    QString m_name;
    /**
     * @brief Construit un groupe de passagers.
     */
    Person();
    /**
     * @brief Détruit un groupe de passagers.
     */
    virtual ~Person();
    /**
     * @brief Représente le comportement d'une personne.
     */
    void run();
    /**
     * @brief Achète un ticket.
     */
    void buyTicket(PurchasingTerminal *);
    /**
     * @brief Composte un ticket.
     */
    void punchTicket(PunchingTerminal *);
    /**
     * @brief Déclenche un arrêt d'urgence.
     */
    void triggerEmergencyStop();
    /**
     * @brief Traite le nouveau message.
     */
    void handleNewMessage();
    /**
     * @brief Change le conteneur. Le conteneur sera de type station ou tram.
     * @param le nouveau conteneur
     */
    void setContainer(Container* c){m_container = c;}
    /**
     * @brief Indique l'état du groupe de passagers.
     * @return l'état du groupe de passagers
     */
    int getState() const {return m_state;}
    /**
     * @brief Retourne le nombre de personnes dans le groupe.
     * @return le nombre de personnes dans le groupe
     */
    int nbPerson() const {return m_nbPerson;}

private:
    /**
     * @brief Rentre dans le tram.
     */
    void getOnTheTram(Container*);
    /**
     * @brief Sort du tram.
     */
    void getOffTheTram(Container*);

private:
    State m_state;
    Container* m_container;
    const int m_nbPerson;
    int m_nbTicketToBuy;
    int m_nbTicketToPunch;
};

#endif // PERSON_H
