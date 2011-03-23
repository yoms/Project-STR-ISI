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

#ifndef TRAMWINDOW_H
#define TRAMWINDOW_H

#include <QMainWindow>
#include "Trip.h"
#include "Obstacle.h"
#include "Tram.h"
#include "Station.h"
#include "Timer.h"
#include "ObstacleWidget.h"
#include "TramPropertiesWidget.h"

namespace Ui {
    class TramWindow;
}

/**
 * @brief Représente un widget qui affiche le trajet.
 */
class TramWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construit le widget.
     * @param l'objet param
     */
    explicit TramWindow(QWidget *parent = 0);
    /**
     * @brief Détruit le widget.
     */
    virtual ~TramWindow();
    /**
     * @brief Représente le parcours 1.
     */
    void setupTrip1();
    /**
     * @brief Représente le parcours 2.
     */
    void setupTrip2();
    /**
     * @brief Charge les TramWidgets et ObstacleWidgets.
     */
    void setupDrawingWidget();

private:
    QList<Trip*> m_trajetList;
    QList<Tram*> m_tramList;
    QList<Obstacle*> m_obstacleList;
    QList<ObstacleWidget*> m_obstacleWidgetList;
    QList<TramPropertiesWidget*> m_tramPropertiesWidgetList;
    QList<Station*> m_stationList;

    Ui::TramWindow *ui;
    Timer *m_timer;
};

#endif // TRAMWINDOW_H
