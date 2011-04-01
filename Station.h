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

#ifndef STATION_H
#define STATION_H
#include "Drawable.h"
#include "StationLight.h"
#include "ThreadWithMessages.h"
#include "Timer.h"
#include "Person.h"
#include "Container.h"
class PurchasingTerminal;
class StationLight;
class Person;

/**
 * @brief Représente une station.
 */
class Station : public Drawable, public Container
{
public:
    /**
     * @brief Construit une station.
     */
    Station();
    /**
     * @brief Detruit une station.
     */
    virtual ~Station();
    /**
     * @brief Dessine une station.
     * @param
     */
    void draw(QPainter *);
    /**
     * @brief Ajoute un feu station.
     * @param un feu station
     */
    void addStationLight(StationLight*);
    /**
     * @brief Indique le nom de la classe.
     * @return le nom de la classe
     */
    virtual QString className() {
        return QString("Station");
    }
    /**
     * @brief Retourne la borne d'achat du tram.
     * @return la borne d'achat du tram
     */
    PurchasingTerminal* purchasingTerminal() {
        return m_purchasingTerminal;
    }
    /**
     * @brief Représente le comportement du feu.
     */
    virtual void run();
    /**
     * @brief Traite le nouveau message.
     */
    void handleNewMessage();
private:
    StationLight* m_stationLight;
    PurchasingTerminal* m_purchasingTerminal;
};

#endif // STATION_H
