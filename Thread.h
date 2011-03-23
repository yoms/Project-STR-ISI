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

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <QString>
#include <QMap>

/**
 * @brief Représente un thread.
 */
class Thread
{

public:
    /**
     * @brief Construit un thread.
     */
    Thread();
    /**
     * @brief Détruit un thread.
     */
    virtual ~Thread();    
    /**
     * @brief Démarre le thread.
     */
    virtual void start();
    /**
     * @brief Arrete le thread.
     */
    virtual void stop();
    /**
     * @brief Joint le thread.
     */
    virtual void join();
    /**
     * @brief Indique si le thread est en marche.
     * @return vrai si le thread est en marche et faux sinon
     */
    bool isRunning();
    /**
     * @brief Représente le comportement du thread.
     */
    virtual void run() = 0;
    /**
     * @brief Indique le nom de la classe.
     * @return le nom de la classe
     */
    virtual QString className(){ return QString("Thread");}
    /**
     * @brief Indique l'id du thread.
     * @return l'id du thread
     */
    pthread_t threadid();

private:
    Thread(const Thread&);
    Thread& operator=(const Thread&);
    friend void *_threadFunc(void *);

protected:
    bool m_running;

private:
    pthread_t m_thread;
    pthread_attr_t m_attr;


};

#endif //THREAD_H
