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

#ifndef TRAM_H
#define TRAM_H
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QList>
#include "Drawable.h"
#include "ThreadWithMessages.h"
#include "Timer.h"
#include "Obstacle.h"
#include "Person.h"
#include "Container.h"

#define NB_DOORS 4
#define NB_COMPOSTER 4
#define NB_EMERGENCY_STOP 4
#define CAPACITE 150

class QPainter;
class Trip;
class Person;
class PunchingTerminal;

/**
 * @brief Représente un tramway.
 */
class Tram : public Drawable, public TimerListener, public Container
{
public:
    /**
     * @brief Représente les différents états d'un tram.
     */
    enum State{
        /**
         * @brief Le tram accélère.
         */
        Acceleration,
        /**
         * @brief Le tram ralenti.
         */
        Desceleration,
        /**
         * @brief Le tram est en marche.
         */
        On,
        /**
         * @brief Le tram est à l'arrêt.
         */
        Off};
    /**
     * @brief Construit un tram.
     */
    Tram();
    /**
     * @brief Détruit le tram.
     */
    virtual ~Tram();
    /**
     * @brief Représente un tour de timer.
     */
    void tick();
    /**
     * @brief Dessine un tram.
     */
    void draw(QPainter *);
    /**
     * @brief Représente le comportement d'un tram.
     */
    void run();
    /**
     * @brief Détecter le prochain obstacle.
     */
    void obstacleTracking();
    /**
     * @brief Avancer.
     */
    void move();
    /**
     * @brief Accélérer.
     */
    void speedUp();
    /**
     * @brief Ralentir.
     */
    void slowDown();
    /**
     * @brief Gère l'arrêt en gare.
     */
    void manageStationStop();
    /**
     * @brief Change le trajet.
     * @param le nouveau trajet
     */
    void setTrip(Trip*);
    /**
     * @brief Retourne la vitesse du tram.
     * @return la vitesse du tram
     */
    int velocity(){return m_velocity;}
    /**
     * @brief Retourne l'état du tram.
     * @return l'état du tram
     */
    Tram::State state(){return m_state;}
    /**
     * @brief Envoie une message pour signifier qu'il est arrété.
     */
    void sendIsStoped();
    /**
     * @brief Retourne le nom de la classe.
     * @return le nom de la classe
     */
    virtual QString className(){ return QString("Tram");}
    /**
     * @brief Retourne le composteur du tram.
     * @return le composteur du tram
     */
    PunchingTerminal* punchingTerminal() {return m_punchingTerminal;}
private:
    void handleNewMessage();
private:
    PunchingTerminal* m_punchingTerminal;
    Trip* m_trip;
    int m_nbTick;
    int m_velocity;
    pthread_mutex_t m_mutexTram;
    State m_state;
    Obstacle* m_obstacle;
};

#endif // TRAM_H
