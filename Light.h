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

#ifndef LIGHT_H
#define LIGHT_H

#include "Obstacle.h"
#include "Drawable.h"
#include "Timer.h"

/**
 * @brief Représente un feu de signalisation.
 */
class Light : public Obstacle
{
public:

    /**
     * @brief Couleur du feu.
     */
    enum Color {
        Green = 0,
        Red
    };
    /**
     * @brief Construit un feu.
     */
    Light();
    /**
     * @brief Détruit le feu.
     */
    virtual ~Light(){}
    /**
     * @brief Indique l'état du feu.
     * @return vrai si le feu est rouge et faux sinon
     */
    bool indicateState();
    /**
     * @brief Dessine le feu.
     */
    void draw(QPainter *);
    /**
     * @brief Représente le comportement du feu.
     */
    void run();
    /**
     * @brief Retourne la couleur du feu.
     * @return la couleur du feu
     */
    Light::Color state();
    /**
     * @brief Retourne le nom de la classe.
     * @return le nom de la classe
     */
    virtual QString className(){ return QString("Light");}
    /**
     * @brief Représente un tour de timer.
     */
    void tick(){}
    /**
     * @brief Change la couleur d'un feu.
     * @param color la nouvelle couleur du feu
     */
    void setColor(Color);
    /**
     * @brief Traite le nouveau message.
     */
    void handleNewMessage();
    /**
     * @brief Change le feu précédent.
     * @param light le feu précédent
     */
    void setPreviousLight(Light*);

protected:
    Color m_state;
    Light * m_previousLight;
};

#endif // LIGHT_H
