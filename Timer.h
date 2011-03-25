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

#ifndef TIMER_H
#define TIMER_H
#include "Thread.h"
#include <QList>
#include <signal.h>
#include <sys/wait.h>

/**
 * @brief Représente un écouteur.
 */
class TimerListener
{
public:
    virtual void tick() = 0;
};

/**
 * @brief Représente un timer.
 */
class Timer : public Thread
{
public:
    /**
     * @brief Construit un timer.
     * @param expiration et périose du timer en seconde
     * @param milliseconde
     * @param nanoseconde
     */
    Timer(int sec, int mSec = 0, int nSec = 0);
    /**
     * @brief Détruit le timer.
     */
    virtual ~Timer();
    /**
     * @brief Ajoute un écouteur.
     * @param le nouvel écouteur
     */
    void addListener(TimerListener* tl);
    /**
     * @brief Supprime un écouteur.
     * @param l'écouteur à supprimer
     */
    void removeListener(TimerListener* tl);
    /**
     * @brief Représente un tour de timer.
     */
    void tick();
    /**
     * @brief Représente le comportement du timer.
     */
    void run();
    /**
     * @brief Arrete le timer.
     */
    void stop();
    /**
     * @brief Indique la classe de l'objet.
     * @return Timer
     */
    virtual QString className(){ return QString("Timer");}
private:
    static void _alarmFunction(int sigNumb, siginfo_t *si, void *uc);
    static void _waitingFunction(int sigNumb, siginfo_t *si, void *uc);
    Timer(){}
private:
    timer_t m_timerID;
    struct sigevent m_signalEvent;
    struct sigaction m_signalAction;
    struct itimerspec m_timerSpecs;
    QList<TimerListener*> m_listenerList;
};

#endif // TIMER_H
