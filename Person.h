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
    void buyTicket();
    /**
     * @brief Composte un ticket.
     */
    void punchTicket();
    /**
     * @brief Rentre dans le tram.
     */
    void getOnTheTram();
    /**
     * @brief Sort du tram.
     */
    void getOffTheTram();
    /**
     * @brief Attend dans la station.
     */
    void waitInStation();
    /**
     * @brief Attend dans le tram.
     */
    void waitInTram();
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
    void setContainer(ThreadWithMessages* t){m_container = t;}
    /**
     * @brief Indique l'état du groupe de passagers.
     * @param l'état du groupe de passagers
     */
    int getState() const {return m_state;}
private:
    State m_state;
    ThreadWithMessages* m_container;
};

#endif // PERSON_H
