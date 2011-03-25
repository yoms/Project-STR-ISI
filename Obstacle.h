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

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QPoint>
#include "ThreadWithMessages.h"
#include "Drawable.h"
#include "Timer.h"

/**
 * @brief Représente un obstacle.
 */
class Obstacle : public Drawable, public ThreadWithMessages, public TimerListener
{
public:
    /**
     * @brief Construit un obstacle.
     */
    Obstacle();
    /**
     * @brief Détruit l'obstacle.
     */
    virtual ~Obstacle(){}
    /**
     * @brief Indique l'état de l'obstacle.
     * @return vrai si le feu est rouge et faux sinon
     */
    virtual bool indicateState() = 0;
    /**
     * @brief Indique le lieu de l'obstacle.
     * @return le lieu
     */
    QPoint place(){return m_place;}
    /**
     * @brief Change le lieu de l'obstacle.
     * @param le nouveau lieu
     */
    void setPlace(QPoint l){m_place = l;}
    /**
     * @brief Indique le nom de la classe.
     * @return le nom de la classe
     */
    virtual QString className(){ return QString("Obstacle");}
private:
    QPoint m_place;
};

#endif // OBSTACLE_H
