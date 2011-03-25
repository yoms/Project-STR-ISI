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

#ifndef OUTDOORSECTIONLIGHT_H
#define OUTDOORSECTIONLIGHT_H
#include "Light.h"
/**
 * @brief Représente un feu tronçon extérieur. Ce feu est placé uniquement sur une voie bidirectionnelle.
 */
class OutdoorSectionLight : public Light
{
public:
    /**
     * @brief Construit un feu tronçon extérieur.
     */
    OutdoorSectionLight();
    /**
     * @brief Détruit un feu tronçon extérieur.
     */
    virtual ~OutdoorSectionLight();

private:
    Light* m_next;
};

#endif // OUTDOORSECTIONLIGHT_H
