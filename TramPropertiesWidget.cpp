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

#include "TramPropertiesWidget.h"
#include "ui_trampropertieswidget.h"
#include "Tram.h"
TramPropertiesWidget::TramPropertiesWidget(Tram* t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TramPropertiesWidget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTramInformation()));
    connect(this->ui->m_name, SIGNAL(clicked()), this, SLOT(updateTramSelection()));
    m_timer->start(50);
    m_tram = t;
}

TramPropertiesWidget::~TramPropertiesWidget()
{
    delete ui;
}

void TramPropertiesWidget::updateTramSelection()
{
    m_tram->isSelect() ? m_tram->unSelect():m_tram->select();;
}

void TramPropertiesWidget::updateTramInformation()
{
    this->ui->m_name->setText(m_tram->name());
    this->ui->m_velocity->setText(QString::number((40 - m_tram->velocity()))+" km/h");
    int nbPersons =  0;
    for(int i = 0 ; i< m_tram->persons().size() ; i++)
    {
        nbPersons += m_tram->persons()[i]->nbPerson();
    }
    this->ui->m_nbPersons->setText(QString::number(nbPersons)+ " passager(s)");
    switch(m_tram->state())
    {
    case Tram::On:
        this->ui->m_state->setText("Marche");
        break;
    case Tram::Off:
        this->ui->m_state->setText("Arret");
        break;
    case Tram::Acceleration:
        this->ui->m_state->setText("Accelere");
        break;
    case Tram::Desceleration:
        this->ui->m_state->setText("Ralenti");
        break;
    case Tram::OutOfOrder:
        this->ui->m_state->setText("En panne");
        break;
    }
}

void TramPropertiesWidget::on_pushButton_clicked()
{
//    m_tram->addMessage(new Message(NULL, Message::Solved));
}

void TramPropertiesWidget::on_m_panne_clicked()
{
//    m_tram->changeProblem(true);
}
