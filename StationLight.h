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

#ifndef STATIONLIGHT_H
#define STATIONLIGHT_H

#include "Light.h"
#include "Station.h"
class Station;
/**
 * @brief Représente un feu station.
 */
class StationLight : public Light
{
public:
    /**
     * @brief Construit un feu station.
     */
    StationLight();
    /**
     * @brief Ajoute la station de rattachement du feu.
     * @param la station de rattachement
     */
    void addStation(Station*);
    /**
     * @brief Représente un tour de timer.
     */
    void tick(){}
    /**
     * @brief Traite le nouveau message.
     */
    void handleNewMessage();
    /**
     * @brief Change le couleur du stage.
     * @param la nouvelle couleur du feu
     */
    void setColor(Color);
private:
    Station* m_station;
    bool m_free;
};

#endif // STATIONLIGHT_H
