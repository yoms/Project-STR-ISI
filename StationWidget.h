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

#ifndef STATIONWIDGET_H
#define STATIONWIDGET_H

#include <QWidget>
#include <QTimer>
class Station;
namespace Ui {
    class StationWidget;
}

/**
 * @brief Représente un widget qui affiche le nombre de personnes dans une station.
 */
class StationWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construit le widget.
     * @param une station
     * @param l'objet parent
     */
    explicit StationWidget(Station* s, QWidget *parent = 0);
    /**
     * @brief Détruit le widget.
     */
    virtual ~StationWidget();
private slots:
    void updateStationInformation();
private:
    Ui::StationWidget *ui;
    QTimer *m_timer;
    Station *m_station;
};

#endif // STATIONWIDGET_H
