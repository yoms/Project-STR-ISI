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

#ifndef TRIP_H
#define TRIP_H
#include "Drawable.h"
#include <QList>
#include <QPoint>
#include "Obstacle.h"
#define DISTANCE_VISION 10

/**
 * @brief Représente un trajet.
 */
class Trip : public Drawable
{
public:
    /**
     * @brief Construit un trajet.
     */
    Trip();
    /**
     * @brief Détruit le trajet.
     */
    virtual ~Trip(){}
    /**
     * @brief Change le trajet retour.
     * @param le nouveau trajet
     */
    void setForward(Trip* t){m_forwardTrip = t;}
    /**
     * @brief Indique le trajet retour
     * @return le trajet
     */
    Trip* forward(){return m_forwardTrip;}
    /**
     * @brief Dessine le trajet.
     * @param
     */
    void draw(QPainter *);
    /**
     * @brief Indique le trajet.
     * @return la liste de points
     */
    QList<QPoint> trip();
    /**
     * @brief Change la liste de points.
     * @param la nouvelle liste de points
     */
    void setTrip(QList<QPoint> &);
    /**
     * @brief Indique le prochain obstacle.
     * @param le point courant
     * @return le prochain obstacle
     */
    Obstacle* obstacleExist(QPoint);
    /**
     * @brief Indique le prochain obstacle.
     * @param le point courant
     * @param distance de vue
     * @return le prochain obstacle
     */
    Obstacle* obstacleExist(QPoint, int);
    /**
     * @brief Indique le point suivant.
     * @param le point courant
     * @return le point suivant
     */
    QPoint next(QPoint);
    /**
     * @brief Indique le point précédent.
     * @param le point courant
     * @return le point précédent
     */
    QPoint previous(QPoint);
    /**
     * @brief Change la liste d'obstacles.
     * @param la nouvelle liste d'obstacles
     */
    void setObstacle(QList<Obstacle*>);
    /**
     * @brief Ajoute un obstacle à la liste.
     * @param le nouvel obstacle
     */
    void addObstacle(Obstacle*);
private:
    QList<QPoint> m_trip;
    QList<Obstacle*> m_obstacle;
    Trip* m_forwardTrip;
    pthread_mutex_t m_mutexTrip;
};

#endif // TRIP_H
