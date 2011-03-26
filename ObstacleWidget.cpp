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

#include "ObstacleWidget.h"
#include "ui_obstaclewidget.h"
#include <QTimer>

ObstacleWidget::ObstacleWidget(Obstacle *obstacle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObstacleWidget)
{
    m_obstacle = obstacle;
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateObstacleInformation()));
    m_timer->start(50);
}

ObstacleWidget::~ObstacleWidget()
{
    delete ui;
}

void ObstacleWidget::updateObstacleInformation()
{
    this->ui->m_name->setText(m_obstacle->name());
    if(m_obstacle->indicateState())
    {
        this->ui->m_color->setStyleSheet("background-color: #00ff00");
    }
    else
    {
        this->ui->m_color->setStyleSheet("background-color: #ff0000");
    }
}

void ObstacleWidget::on_m_etat_clicked()
{
    m_obstacle->changeState();
}
