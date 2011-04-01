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

#include "StationWidget.h"
#include "ui_stationwidget.h"
#include "Station.h"
StationWidget::StationWidget(Station* s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StationWidget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateStationInformation()));
    m_timer->start(50);
    m_station = s;
}

StationWidget::~StationWidget()
{
    delete ui;
}

void StationWidget::updateStationInformation()
{
    this->ui->m_name->setText(m_station->name());
    int nbPersons =  0;
    for(int i = 0 ; i < m_station->persons().size() ; i++) {
        nbPersons += m_station->persons()[i]->nbPerson();
    }
    this->ui->m_nbPersons->setText(QString::number(nbPersons) + " passager(s)");
}
