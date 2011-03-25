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
#include "Thread.h"
class Station;
class Tram;

/**
 * @brief Représente un passager.
 */
class Person : public Thread
{
public:
    enum Etat{
        NeedTicket,
        NeedGetOnTheTram,
        NeedGetOffTheTram
    };
    Person();
    /**
     * @brief Indique la station.
     * @return la station
     */
    Station* station(){return m_station;}
    /**
     * @brief Change la station.
     * @param le nouvelle station
     */
    void setStation(Station* s){m_station = s;}
    /**
     * @brief Indique le tram.
     * @return le tram
     */
    Tram* tram(){return m_tram;}
    /**
     * @brief Change le tram.
     * @param le nouveau tram
     */
    void setTram(Tram* t){m_tram = t;}
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
private:
    Station *m_station;
    Tram *m_tram;
    Etat m_etat;
};

#endif // PERSON_H
